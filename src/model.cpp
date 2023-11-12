#include "model.hpp"

#include <OpenXLSX.hpp>
#include <QFile>
#include <set>

#include "exception.hpp"

Model::Model() {}

std::vector<InputFormat> &Model::getData() { return m_details; }

std::vector<TextureExchange> &Model::getExchange() { return m_exchanges; }

const std::vector<InputFormat> &Model::getData() const { return m_details; }

const std::vector<TextureExchange> &Model::getExchange() const {
  return m_exchanges;
}

QString &Model::getBorderName() { return m_border_name; }

InputBorder &Model::getBorderType() { return m_default_border; }

const QString &Model::getBorderName() const { return m_border_name; }

const InputBorder &Model::getBorderType() const { return m_default_border; }

void Model::LoadFromFile(QString name) {
  QFile file(name);
  file.open(QIODevice::ReadOnly);

  std::vector<InputFormat> from;

  std::set<QString> materials;

  while (!file.atEnd()) {
    auto array = file.readLine();
    auto parts = QString(array).split("\t");

    parts[7].replace("\\", "");
    parts[7].replace("\r\n", "");
    parts[7].replace("\r", "");

    InputFormat e;
    e.setName(parts[0]);
    e.setWidth(parts[1]);
    e.setWidthBorder(parts[2]);
    e.setHeight(parts[3]);
    e.setHeightBorder(parts[4]);
    e.setThickness(parts[5]);
    e.setCount(parts[6]);
    e.setMaterial(parts[7]);

    from.push_back(e);
    materials.insert(parts[7]);
  }

  std::vector<TextureExchange> exchange;
  for (auto elem : materials) {
    TextureExchange e;
    e.setFrom(elem);
    exchange.push_back(e);
  }

  m_exchanges = exchange;
  m_details = from;
}

void Model::ExportToViyar(QString name) const {
  struct to_entry {
    int width;
    int height;
    int count;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    QString texture_rotate = "-";
    QString name;
  };

  struct to_struct {
    QString hash;
    std::vector<to_entry> entries;
  };

  std::map<std::string, std::vector<to_entry>> to;

  for (auto f : m_details) {
    auto material = f.getMaterial();
    auto hash =
        QString::number(f.getThickness()) + "mm " + exchangeTexture(material);

    to_entry e;
    e.name = f.getName();
    e.width = f.getWidth();
    e.height = f.getHeight();
    e.count = f.getCount();

    e.up = ((f.getWidthBorder() != NOBORDER) ? m_default_border : NOBORDER)
               .value();
    e.down =
        ((f.getWidthBorder() == BORDER2) ? m_default_border : NOBORDER).value();

    e.left = ((f.getHeightBorder() != NOBORDER) ? m_default_border : NOBORDER)
                 .value();
    e.right = ((f.getHeightBorder() == BORDER2) ? m_default_border : NOBORDER)
                  .value();

    to[hash.toStdString()].push_back(e);
  }

  for (auto elem : to) {
    QFile ofile(name + "/" + QString::fromStdString(elem.first) + ".csv");

    ofile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

    for (auto line : elem.second) {
      QString const text =
          QString::number(line.width) + "," + QString::number(line.height) +
          "," + QString::number(line.count) + "," + QString::number(line.up) +
          "," + QString::number(line.down) + "," + QString::number(line.left) +
          "," + QString::number(line.right) + "," + line.texture_rotate + "," +
          line.name + "," + "\n";
      ofile.write(text.toUtf8());
    }

    ofile.close();
  }
}

void Model::ExportToGibLab(QString name) const {
  if (m_border_name == "") throw ExportException("Не задана назва кромки");

  struct to_entry {
    QString material;
    int height;
    int width;
    int count;
    int texture_rotate = 1;
    QString name;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    QString description = "";
  };

  std::vector<to_entry> to;

  for (auto f : m_details) {
    auto material = f.getMaterial();

    to_entry e;

    e.material = exchangeTexture(material);
    e.height = f.getHeight();
    e.width = f.getWidth();
    e.count = f.getCount();
    e.name = f.getName();
    e.up = ((f.getWidthBorder() != NOBORDER) ? m_default_border : NOBORDER)
               .value();
    e.down =
        ((f.getWidthBorder() == BORDER2) ? m_default_border : NOBORDER).value();
    e.left = ((f.getHeightBorder() != NOBORDER) ? m_default_border : NOBORDER)
                 .value();
    e.right = ((f.getHeightBorder() == BORDER2) ? m_default_border : NOBORDER)
                  .value();

    to.push_back(e);
  }

  using namespace OpenXLSX;
  XLDocument doc;
  doc.create(name.toStdString());
  auto wks = doc.workbook().worksheet("Sheet1");

  for (int i = 0; i < to.size(); i++) {
    wks.cell(i + 1, 1).value() = to[i].material.toStdString();
    wks.cell(i + 1, 2).value() = to[i].height;
    wks.cell(i + 1, 3).value() = to[i].width;
    wks.cell(i + 1, 4).value() = to[i].count;
    wks.cell(i + 1, 5).value() = to[i].texture_rotate;
    wks.cell(i + 1, 6).value() = to[i].name.toStdString();
    wks.cell(i + 1, 7).value() = (to[i].up ? m_border_name.toStdString() : "");
    wks.cell(i + 1, 8).value() =
        (to[i].down ? m_border_name.toStdString() : "");
    wks.cell(i + 1, 9).value() =
        (to[i].left ? m_border_name.toStdString() : "");
    wks.cell(i + 1, 10).value() =
        (to[i].right ? m_border_name.toStdString() : "");
    wks.cell(i + 1, 11).value() = to[i].description.toStdString();
  }

  doc.save();
}

QString Model::exchangeTexture(QString from) const {
  for (auto texture : m_exchanges) {
    if (texture.getFrom() == from) {
      if (texture.getTo() == "") return texture.getFrom();
      return texture.getTo();
    }
  }
  return "";
}
