#include "controller.hpp"

#include <QFileDialog>
#include <QMessageBox>

#include "exception.hpp"

Controller::Controller()
{
  
}

const Model *Controller::getModel() const { return m_model; }

void Controller::setModel(Model *Model) { m_model = Model; }

void Controller::detailsTablesChanged(int row, int column, QString new_value) {
  switch (column) {
    case 0:
      m_model->getData()[row].setName(new_value);
      break;
    case 1:
      m_model->getData()[row].setWidth(new_value);
      break;
    case 2:
      m_model->getData()[row].setWidthBorder(new_value);
      break;
    case 3:
      m_model->getData()[row].setHeight(new_value);
      break;
    case 4:
      m_model->getData()[row].setHeightBorder(new_value);
      break;
    case 5:
      m_model->getData()[row].setThickness(new_value);
      break;
    case 6:
      m_model->getData()[row].setCount(new_value);
      break;
    case 7:
      m_model->getData()[row].setMaterial(new_value);
      m_model->UpdateMaterials();
      break;
    default:
      break;
  }
}

void Controller::exchangesTablesChanged(int row, int column,
                                        QString new_value) {
  switch (column) {
    case 0:
      break;
    case 1:
      m_model->getExchange()[row].setTo(new_value);
      break;
    default:
      break;
  }
}

void Controller::deleteDetail(int index) {
  if (index < m_model->getData().size())
    m_model->getData().erase(m_model->getData().begin() + index);
}

void Controller::Import() {
  try {
    m_model->LoadFromFile(QFileDialog::getOpenFileName(
        nullptr, "Введіть файл з PRO100", {}, "*.txt"));
  } catch (ExportException e) {
    QMessageBox::warning(nullptr, "Помилка імпорту", e.what());
    return;
  }
  QMessageBox::information(nullptr, "Інформація", "Експорт успішно виконано");
}

void Controller::ExportViyar() {
  try {
    auto url = QFileDialog::getExistingDirectory(
        nullptr, "Виберіть папку для збереження", {});
    if (url != "")
      m_model->ExportToViyar(url);
    else
      return;
  } catch (ExportException e) {
    QMessageBox::warning(nullptr, "Помилка експорту", e.what());
    return;
  }
  QMessageBox::information(nullptr, "Інформація", "Імпорт успішно виконано");
}
