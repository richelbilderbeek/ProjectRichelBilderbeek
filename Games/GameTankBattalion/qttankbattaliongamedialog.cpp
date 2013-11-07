//---------------------------------------------------------------------------
#include "dialoggame.h"
#include "qtgamewidget.h"
#include "ui_dialoggame.h"
//---------------------------------------------------------------------------
DialogGame::DialogGame(QWidget *parent)
  : QDialog(parent),
    m_game(new QtGameWidget),
    ui(new Ui::DialogGame)
{
  ui->setupUi(this);
  ui->layout->addWidget(m_game.get());
}
//---------------------------------------------------------------------------
DialogGame::~DialogGame()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogGame::changeEvent(QEvent *e)
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
