#ifndef INPUTFORMAT_HPP
#define INPUTFORMAT_HPP

#include <QString>

class InputBorder {
 public:
  constexpr InputBorder() : m_type(0){};
  constexpr InputBorder(int type) : m_type(type){};

  void FromString(QString value) {
    if (value == "")
      m_type = 0;
    else if (value == "-")
      m_type = 1;
    else if (value == "—")
      m_type = 1;
    else if (value == "=")
      m_type = 2;
    else if (value == "0")
      m_type = 0;
    else if (value == "1")
      m_type = 1;
    else if (value == "2")
      m_type = 2;
  };
  QString ToString() const {
    switch (m_type) {
      case 0:
        return "";
      case 1:
        return "-";
      case 2:
        return "=";
    }
  };

  bool operator==(InputBorder b2) const { return m_type == b2.m_type; }
  bool operator!=(InputBorder b2) const { return m_type != b2.m_type; }

  int value() const { return m_type; }

 private:
  int m_type;
};

const static InputBorder NOBORDER{0};
const static InputBorder BORDER1{1};
const static InputBorder BORDER2{2};

class TextureExchange {
 public:
  QString getFrom() const;
  void setFrom(const QString &From);

  QString getTo() const;
  void setTo(const QString &To);

 private:
  QString m_from = "";
  QString m_to = "";
};

class InputFormat {
 public:
  InputFormat();

  size_t getWidth() const;
  QString getWidthS() const;
  void setWidth(size_t Width);
  void setWidth(QString Width);

  InputBorder getWidthBorder() const;
  QString getWidthBorderS() const;
  void setWidthBorder(InputBorder Width_border);
  void setWidthBorder(QString Width_border);

  size_t getHeight() const;
  QString getHeightS() const;
  void setHeight(size_t Height);
  void setHeight(QString Height);

  InputBorder getHeightBorder() const;
  QString getHeightBorderS() const;
  void setHeightBorder(InputBorder Height_border);
  void setHeightBorder(QString Height_border);

  size_t getThickness() const;
  QString getThicknessS() const;
  void setThickness(size_t Thickness);
  void setThickness(QString Thickness);

  size_t getCount() const;
  QString getCountS() const;
  void setCount(size_t Count);
  void setCount(QString Count);

  QString getName() const;
  void setName(const QString &Name);

  QString getMaterial() const;
  void setMaterial(const QString &Material);

 private:
  size_t m_width;
  InputBorder m_width_border;
  size_t m_height;
  InputBorder m_height_border;

  size_t m_thickness;

  size_t m_count;

  QString m_name;
  QString m_material;
};

#endif // INPUTFORMAT_HPP
