#include "model.hpp"

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

void Model::LoadFromFile(QString name) {
  QFile file(name);
  file.open(QIODevice::ReadOnly);

  if (!file.isOpen()) throw ExportException("Помилка відкриття файлу");

  std::vector<InputFormat> from;

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
  }
  m_details = from;

  UpdateMaterials();
}

void Model::UpdateMaterials() {
  std::set<QString> materials;
  for (auto detail : m_details) {
    auto hash =
        QString::number(detail.getThickness()) + "mm " + detail.getMaterial();
    materials.insert(hash);
  }
  std::vector<TextureExchange> exchange;
  for (auto elem : materials) {
    TextureExchange e;
    e.setFrom(elem);
    exchange.push_back(e);
  }

  m_exchanges = exchange;
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
        exchangeTexture(QString::number(f.getThickness()) + "mm " + material);

    to_entry e;
    e.name = f.getName();
    e.width = f.getWidth();
    e.height = f.getHeight();
    e.count = f.getCount();

    e.up = ((f.getWidthBorder() != NOBORDER) ? BORDER1 : NOBORDER).value();
    e.down = ((f.getWidthBorder() == BORDER2) ? BORDER1 : NOBORDER).value();

    e.left = ((f.getHeightBorder() != NOBORDER) ? BORDER1 : NOBORDER).value();
    e.right = ((f.getHeightBorder() == BORDER2) ? BORDER1 : NOBORDER).value();

    to[hash.toStdString()].push_back(e);
  }

  for (auto elem : to) {
    QFile ofile(name + "/" + QString::fromStdString(elem.first) + ".csv");
    ofile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    if (!ofile.isOpen()) throw ExportException("Помилка збереження в файл");

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

QString Model::exchangeTexture(QString from) const {
  for (auto texture : m_exchanges) {
    if (texture.getFrom() == from) {
      if (texture.getTo() == "") return texture.getFrom();
      return texture.getTo();
    }
  }
  return "";
}
