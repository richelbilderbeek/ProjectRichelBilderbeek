#ifndef SKETCHWIDGET_H
#define SKETCHWIDGET_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QWidget>
#pragma GCC diagnostic pop

class SketchWidget : public QWidget
{
  Q_OBJECT
public:
  explicit SketchWidget(QWidget *parent = 0);
  void clear();

protected:
  void mouseMoveEvent(QMouseEvent *);
  void mousePressEvent(QMouseEvent *);
  void paintEvent(QPaintEvent *);

private:
  std::vector<std::vector<QPoint>> m_points;
};

#endif // SKETCHWIDGET_H
