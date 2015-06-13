#ifndef QTMUTUALISMBREAKDOWNERSPATIALWIDGET_H
#define QTMUTUALISMBREAKDOWNERSPATIALWIDGET_H

#include <QWidget>
#include <QImage>

namespace Ui {
  class QtMutualismBreakdownerSpatialWidget;
}

struct QImage;

namespace ribi {
namespace mb {

class QtMutualismBreakdownerSpatialWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerSpatialWidget(
    const int width = 600,
    const int height = 400,
    QWidget *parent = 0
  );
  QtMutualismBreakdownerSpatialWidget(const QtMutualismBreakdownerSpatialWidget&) = delete;
  QtMutualismBreakdownerSpatialWidget& operator=(const QtMutualismBreakdownerSpatialWidget&) = delete;
  ~QtMutualismBreakdownerSpatialWidget();

  void SetPixel(const int x, const int y, const QColor color);
  void SetResolution(const int width, const int height);

protected:
  void paintEvent(QPaintEvent *);
private:
  Ui::QtMutualismBreakdownerSpatialWidget *ui;
  QImage m_image;
};

} //~namespace mb
} //~namespace ribi

#endif // QTMUTUALISMBREAKDOWNERSPATIALWIDGET_H
