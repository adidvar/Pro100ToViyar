#ifndef VIEW_HPP
#define VIEW_HPP

#include <QTableWidgetItem>
#include <QWidget>

#include "controller.hpp"

namespace Ui {
class View;
}

class View : public QWidget
{
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr);
  ~View();

  Controller *getController() const;
  void setController(Controller *Controller);

  void UpdateFromModel();

 private slots:
  void on_load_clicked();

  void on_details_itemChanged(QTableWidgetItem *item);

  void on_exchanges_itemChanged(QTableWidgetItem *item);

  void on_pushButton_clicked();

  void on_delete_2_clicked();

 private:
  Ui::View *ui;
  Controller *m_controller;
  bool m_editing = false;
};

#endif // VIEW_HPP
