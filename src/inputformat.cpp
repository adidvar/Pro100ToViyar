#include "inputformat.hpp"

InputFormat::InputFormat()
{
  
}

size_t InputFormat::getWidth() const { return m_width; }

QString InputFormat::getWidthS() const { return QString::number(m_width); }

void InputFormat::setWidth(size_t Width) { m_width = Width; }

void InputFormat::setWidth(QString Width) { m_width = Width.toInt(); }

InputBorder InputFormat::getWidthBorder() const { return m_width_border; }

QString InputFormat::getWidthBorderS() const {
  return m_width_border.ToString();
}

void InputFormat::setWidthBorder(InputBorder Width_border) {
  m_width_border = Width_border;
}

void InputFormat::setWidthBorder(QString Width_border) {
  m_width_border.FromString(Width_border);
}

size_t InputFormat::getHeight() const { return m_height; }

QString InputFormat::getHeightS() const { return QString::number(m_height); }

void InputFormat::setHeight(size_t Height) { m_height = Height; }

void InputFormat::setHeight(QString Height) { m_height = Height.toInt(); }

InputBorder InputFormat::getHeightBorder() const { return m_height_border; }

QString InputFormat::getHeightBorderS() const {
  return m_height_border.ToString();
}

void InputFormat::setHeightBorder(InputBorder Height_border) {
  m_height_border = Height_border;
}

void InputFormat::setHeightBorder(QString Height_border) {
  m_height_border.FromString(Height_border);
}

size_t InputFormat::getThickness() const { return m_thickness; }

QString InputFormat::getThicknessS() const {
  return QString::number(m_thickness);
}

void InputFormat::setThickness(size_t Thickness) { m_thickness = Thickness; }

void InputFormat::setThickness(QString Thickness) {
  m_thickness = Thickness.toInt();
}

size_t InputFormat::getCount() const { return m_count; }

QString InputFormat::getCountS() const { return QString::number(m_count); }

void InputFormat::setCount(size_t Count) { m_count = Count; }

void InputFormat::setCount(QString Count) { m_count = Count.toInt(); }

QString InputFormat::getName() const { return m_name; }

void InputFormat::setName(const QString &Name) { m_name = Name; }

QString InputFormat::getMaterial() const { return m_material; }

void InputFormat::setMaterial(const QString &Material) {
  m_material = Material;
}

QString TextureExchange::getFrom() const { return m_from; }

void TextureExchange::setFrom(const QString &From) { m_from = From; }

QString TextureExchange::getTo() const { return m_to; }

void TextureExchange::setTo(const QString &To) { m_to = To; }
