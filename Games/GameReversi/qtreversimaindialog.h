#ifndef QTREVERSIMAINDIALOG_H
#define QTREVERSIMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtReversiMainDialog;
}

namespace ribi {
namespace reversi {

struct QtWidget;

class QtReversiMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtReversiMainDialog(QWidget *parent = 0);
  QtReversiMainDialog(const QtReversiMainDialog&) = delete;
  QtReversiMainDialog& operator=(const QtReversiMainDialog&) = delete;
  ~QtReversiMainDialog() noexcept;


private:
  Ui::QtReversiMainDialog *ui;
  boost::shared_ptr<QtWidget> m_reversi;
};

} //~namespace reversi
} //~namespace ribi

#endif // QTREVERSIMAINDIALOG_H
