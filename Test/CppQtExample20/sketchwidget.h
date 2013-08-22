#ifndef SKETCHWIDGET_H
#define SKETCHWIDGET_H
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include <QWidget>
//---------------------------------------------------------------------------
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
  std::vector<std::vector<QPoint> > m_points;

signals:

public slots:

};
//---------------------------------------------------------------------------
#endif // SKETCHWIDGET_H
