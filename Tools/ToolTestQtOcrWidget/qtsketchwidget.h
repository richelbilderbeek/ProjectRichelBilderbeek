#ifndef QTSKETCHWIDGET_H
#define QTSKETCHWIDGET_H

#include <QWidget>

///Qt example
class QtSketchWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtSketchWidget(QWidget *parent = 0);
  void clear();
  virtual ~QtSketchWidget() {}

protected:
  void mouseMoveEvent(QMouseEvent *);
  void mousePressEvent(QMouseEvent *);
  void paintEvent(QPaintEvent *);

private:
  std::vector<std::vector<QPoint> > m_points;
signals:

public slots:

};

#endif // QTSKETCHWIDGET_H
