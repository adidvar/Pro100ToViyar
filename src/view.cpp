#include "view.hpp"

#include "ui_view.h"

View::View(QWidget *parent) :
                              QWidget(parent),
                              ui(new Ui::View)
{
  ui->setupUi(this);
  ui->details->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->exchanges->setSelectionBehavior(QAbstractItemView::SelectRows);
}

View::~View()
{
  delete ui;
}

Controller *View::getController() const { return m_controller; }

void View::setController(Controller *Controller) { m_controller = Controller; }

void View::UpdateFromModel() {
  const Model *model = m_controller->getModel();
  m_editing = true;

  auto details = model->getData();
  ui->details->setRowCount(details.size());
  for (int i = 0; i < details.size(); ++i) {
    auto item = new QTableWidgetItem(details[i].getName());
    ui->details->setItem(i, 0, item);
    item = new QTableWidgetItem(details[i].getWidthS());
    ui->details->setItem(i, 1, item);
    item = new QTableWidgetItem(details[i].getWidthBorderS());
    ui->details->setItem(i, 2, item);
    item = new QTableWidgetItem(details[i].getHeightS());
    ui->details->setItem(i, 3, item);
    item = new QTableWidgetItem(details[i].getHeightBorderS());
    ui->details->setItem(i, 4, item);
    item = new QTableWidgetItem(details[i].getThicknessS());
    ui->details->setItem(i, 5, item);
    item = new QTableWidgetItem(details[i].getCountS());
    ui->details->setItem(i, 6, item);
    item = new QTableWidgetItem(details[i].getMaterial());
    ui->details->setItem(i, 7, item);
  }

  auto exchanges = model->getExchange();
  ui->exchanges->setRowCount(exchanges.size());
  for (int i = 0; i < exchanges.size(); ++i) {
    auto item = new QTableWidgetItem(exchanges[i].getFrom());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->exchanges->setItem(i, 0, item);
    item = new QTableWidgetItem(exchanges[i].getTo());
    ui->exchanges->setItem(i, 1, item);
  }

  m_editing = false;
}

void View::on_load_clicked() {
  m_controller->Import();
  UpdateFromModel();
}

void View::on_details_itemChanged(QTableWidgetItem *item) {
  if (m_editing) return;
  m_controller->detailsTablesChanged(item->row(), item->column(), item->text());
  UpdateFromModel();
}

void View::on_exchanges_itemChanged(QTableWidgetItem *item) {
  if (m_editing) return;
  m_controller->exchangesTablesChanged(item->row(), item->column(),
                                       item->text());
  UpdateFromModel();
}

void View::on_pushButton_clicked() { m_controller->ExportViyar(); }

void View::on_delete_2_clicked() {
  m_controller->deleteDetail(ui->details->currentRow());
  UpdateFromModel();
}
