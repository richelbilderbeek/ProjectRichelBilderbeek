#ifndef QTSTAIRCASECARDCREATORMAINDIALOG_H
#define QTSTAIRCASECARDCREATORMAINDIALOG_H

//#include <string>
//#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtStaircaseCardCreatorMainDialog;
}

namespace ribi {
namespace scc {

class QtStaircaseCardCreatorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtStaircaseCardCreatorMainDialog(QWidget *parent = 0) noexcept;
  QtStaircaseCardCreatorMainDialog(const QtStaircaseCardCreatorMainDialog&) = delete;
  QtStaircaseCardCreatorMainDialog& operator=(const QtStaircaseCardCreatorMainDialog&) = delete;
  ~QtStaircaseCardCreatorMainDialog() noexcept;

private:
  Ui::QtStaircaseCardCreatorMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace scc
} //~namespace ribi

#endif // QTSTAIRCASECARDCREATORMAINDIALOG_H
