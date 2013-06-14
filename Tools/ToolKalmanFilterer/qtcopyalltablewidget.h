#ifndef QTCOPYALLTABLEWIDGET_H
#define QTCOPYALLTABLEWIDGET_H

#include <QTableWidget>

class QtCopyAllTableWidget : public QTableWidget
{
  public:
  QtCopyAllTableWidget(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);
};

#endif // QTCOPYALLTABLEWIDGET_H
