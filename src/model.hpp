#ifndef MODEL_HPP
#define MODEL_HPP

#include "inputformat.hpp"

class Model {
 public:
  Model();

  std::vector<InputFormat>& getData();
  std::vector<TextureExchange>& getExchange();

  const std::vector<InputFormat>& getData() const;
  const std::vector<TextureExchange>& getExchange() const;

  void LoadFromFile(QString name);
  void UpdateMaterials();

  void ExportToViyar(QString name) const;
  void ExportToGibLab(QString name) const;

 private:
  QString exchangeTexture(QString from) const;

  std::vector<InputFormat> m_details;
  std::vector<TextureExchange> m_exchanges;
};

#endif // MODEL_HPP
