#ifndef QTCOPYALLTABLEVIEW_H
#define QTCOPYALLTABLEVIEW_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QTableView>
#pragma GCC diagnostic pop

#include <string>
#include <vector>

namespace ribi {

class QtCopyAllTableView : public QTableView
{
  public:
  explicit QtCopyAllTableView(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);
};

} //~namespace ribi

#endif // QTCOPYALLTABLEVIEW_H
