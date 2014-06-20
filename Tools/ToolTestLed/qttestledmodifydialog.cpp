#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestledmodifydialog.h"

#include <boost/make_shared.hpp>

#include "qtled.h"
#include "qtleddialog.h"

#include "ui_qttestledmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestLedModifyDialog::QtTestLedModifyDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestLedModifyDialog),
    m_dialog_left(boost::make_shared<QtLedDialog>()),
    m_dialog_right(boost::make_shared<QtLedDialog>()),
    m_led_left(boost::make_shared<QtLed>()),
    m_led_right(boost::make_shared<QtLed>())

{
  ui->setupUi(this);
}

ribi::QtTestLedModifyDialog::~QtTestLedModifyDialog() noexcept
{
  delete ui;
}
