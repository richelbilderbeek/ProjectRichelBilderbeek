#ifndef QTFRACTIONIMAGE_H
#define QTFRACTIONIMAGE_H

#include <vector>
#include <QWidget>
#include <QImage>

///Displays fractions
class QtFractionImage : public QWidget
{
  Q_OBJECT
  public:
  typedef std::vector<std::vector<double>> Grid;
  explicit QtFractionImage(QWidget *parent = 0);
  void paintEvent(QPaintEvent *);

  static int GetWidth() { return m_width; }
  static int GetHeight() { return m_height; }

  void Set(const Grid& grid);

  signals:

  public slots:


  private:
  static void Test() noexcept;
  static const int m_width{128};
  static const int m_height{128};
  QImage m_image;
};

#endif // QTFRACTIONIMAGE_H
