#ifndef QTCOPYALLTABLEVIEW_H
#define QTCOPYALLTABLEVIEW_H

#include <QTableView>

class QtCopyAllTableView : public QTableView
{
  public:
  QtCopyAllTableView(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);
};

#endif // QTCOPYALLTABLEVIEW_H
