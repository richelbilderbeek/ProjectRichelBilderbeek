#ifndef QTTESTREVERSIMAINDIALOG_H
#define QTTESTREVERSIMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestReversiMainDialog;
}

namespace ribi {

namespace reversi { struct QtWidget; }

class QtTestReversiMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestReversiMainDialog(QWidget *parent = 0);
  QtTestReversiMainDialog(const QtTestReversiMainDialog&) = delete;
  QtTestReversiMainDialog& operator=(const QtTestReversiMainDialog&) = delete;
  ~QtTestReversiMainDialog();


private:
  Ui::QtTestReversiMainDialog *ui;
  boost::shared_ptr<reversi::QtWidget> m_reversi;
};

} //~namespace ribi

#endif // QTTESTREVERSIMAINDIALOG_H
