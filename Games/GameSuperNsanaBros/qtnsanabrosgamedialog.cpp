//---------------------------------------------------------------------------
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#include <QKeyEvent>
//---------------------------------------------------------------------------
#include "nsanabrosqtheader.h"
#include "ui_qtnsanabrosgamedialog.h"
//---------------------------------------------------------------------------
QtNsanaBrosGameDialog::QtNsanaBrosGameDialog(
  const NsanaBrosOptions * const options,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtNsanaBrosGameDialog),
    m_game(new NsanaBrosGame)
{
  TRACE_FUNC();
  ui->setupUi(this);

  if (!options) return;

  //if (options->GetShowOneDimension())
  //{
  //  QtNsanaBrosGameArea1dWidget * widget
  //    = new QtNsanaBrosGameArea1dWidget(
  //      m_game);
  //  ui->layout->addWidget(widget);
  //}
  if (options->GetShowTwoDimension())
  {
    QtNsanaBrosGameArea2dWidget * widget
      = new QtNsanaBrosGameArea2dWidget(
        m_game.get());
    ui->layout->addWidget(widget);
  }
  if (options->GetShowKeys())
  {
    QtNsanaBrosKeysWidget * widget
      = new QtNsanaBrosKeysWidget(
        m_game->GetKeys());
    ui->layout->addWidget(widget);
  }

  QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(OnTimerQt()));
  m_timer.setInterval(50);
  m_timer.start();
}
//---------------------------------------------------------------------------
QtNsanaBrosGameDialog::~QtNsanaBrosGameDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtNsanaBrosGameDialog::changeEvent(QEvent *e)
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
void QtNsanaBrosGameDialog::keyPressEvent(QKeyEvent * e)
{
  m_game->KeyPress(e->key());
}
//---------------------------------------------------------------------------
void QtNsanaBrosGameDialog::keyReleaseEvent(QKeyEvent * e)
{
  m_game->KeyRelease(e->key());
}
//---------------------------------------------------------------------------
void QtNsanaBrosGameDialog::OnTimerQt()
{
  m_game->OnTimer();
}
//---------------------------------------------------------------------------
