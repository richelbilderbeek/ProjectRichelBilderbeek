#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "nsanabroskeys.h"
#include "nsanabrosqtheader.h"
#include "ui_qtnsanabrosoptionsdialog.h"
#pragma GCC diagnostic pop

ribi::QtNsanaBrosOptionsDialog::QtNsanaBrosOptionsDialog(
  const NsanaBrosOptions * const ,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtNsanaBrosOptionsDialog),
    m_dialog{}
{
  TRACE_FUNC();
  ui->setupUi(this);

  NsanaBrosKeys::SetKeyUp(Qt::Key_Up);
  NsanaBrosKeys::SetKeyDown(Qt::Key_Down);
  NsanaBrosKeys::SetKeyLeft(Qt::Key_Left);
  NsanaBrosKeys::SetKeyRight(Qt::Key_Right);
}

ribi::QtNsanaBrosOptionsDialog::~QtNsanaBrosOptionsDialog()
{
  delete ui;
}


