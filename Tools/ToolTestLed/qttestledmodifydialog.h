#ifndef QTTESTLEDMODIFYDIALOG_H
#define QTTESTLEDMODIFYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"

#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestLedModifyDialog;
}

namespace ribi {

struct QtLed;
struct QtLedDialog;

class QtTestLedModifyDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestLedModifyDialog(QWidget *parent = 0);
  QtTestLedModifyDialog(const QtTestLedModifyDialog&) = delete;
  QtTestLedModifyDialog& operator=(const QtTestLedModifyDialog&) = delete;
  ~QtTestLedModifyDialog() noexcept;

private:
  Ui::QtTestLedModifyDialog *ui;

  boost::shared_ptr<QtLedDialog> m_dialog_left;
  boost::shared_ptr<QtLedDialog> m_dialog_right;
  boost::shared_ptr<QtLed> m_led_left;
  boost::shared_ptr<QtLed> m_led_right;
};

} //~namespace ribi

#endif // QTTESTLEDMODIFYDIALOG_H
