//---------------------------------------------------------------------------
#include "dialogmain.h"
#include "reversiwidget.h"
#include "ui_dialogmain.h"
//---------------------------------------------------------------------------
DialogMain::DialogMain(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogMain),
  m_reversi(new ReversiWidget)
{
  ui->setupUi(this);

  ui->layout->addWidget(m_reversi.get());
}
//---------------------------------------------------------------------------
DialogMain::~DialogMain()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogMain::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------
