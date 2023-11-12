#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "model.hpp"

class Controller
{
 public:
  Controller();

  const Model *getModel() const;
  void setModel(Model *Model);

  void detailsTablesChanged(int row, int column, QString new_value);
  void exchangesTablesChanged(int row, int column, QString new_value);

  void deleteDetail(int index);

  void Import();
  void ExportViyar();

 private:
  Model *m_model = nullptr;
};

#endif // CONTROLLER_HPP
