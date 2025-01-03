#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QVector>
#include <view.hpp>

struct from_entry {};

QDir createDirectory(QString input) {
  QFileInfo info(input);
  QDir dir_ = info.dir();
  dir_.mkdir(info.fileName() + " Результат");
  dir_.cd(info.fileName() + " Результат");
  return dir_;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto model = new Model();
  auto controller = new Controller();
  controller->setModel(model);
  auto view = new View();
  view->setController(controller);

  view->show();

  return a.exec();

  /*
  auto input_file = QFileDialog::getOpenFileName(
      nullptr, "Введіть файл з PRO100", {}, "*.txt");
  auto root_dir = createDirectory(input_file);

  QFile file(input_file);
  file.open(QIODevice::ReadOnly);

  std::vector<from_entry> from;
  std::map<std::string, std::vector<to_entry>> to;

  while (!file.atEnd()) {
    auto array = file.readLine();
    auto parts = QString(array).split("\t");

    from_entry e;
    e.width = parts[1].toInt();
    e.height = parts[3].toInt();
    e.thickness = parts[5].toInt();
    e.count = parts[6].toInt();
    e.material = parts[7];

    from.push_back(e);
  }

  for (auto f : from) {
    auto material = f.material;
    material.replace("\\", " ");
    material.replace("\r\n", "");
    auto hash = QString::number(f.thickness) + ' ' + material;

    to_entry e;
    e.width = f.width;
    e.height = f.height;
    e.count = f.count;

    to[hash.toStdString()].push_back(e);
  }

  for (auto elem : to) {
    QFile ofile(root_dir.path() + "/" + QString::fromStdString(elem.first) +
                ".csv");
    qDebug() << ofile.fileName();

    ofile.open(QIODevice::WriteOnly | QIODevice::Truncate);

    for (auto line : elem.second) {
      QString text =
          QString::number(line.width) + "," + QString::number(line.height) +
          "," + QString::number(line.count) + "," + QString::number(line.up) +
          "," + QString::number(line.down) + "," + QString::number(line.left) +
          "," + QString::number(line.right) + "," + line.texture_rotate + "," +
          "," + "\r\n";
      ofile.write(text.toUtf8());
    }

    ofile.close();
  }
*/
}
