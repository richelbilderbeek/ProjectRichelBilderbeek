#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>

#include <QKeyEvent>

#include "nsanabrosqtheader.h"
#include "ui_qtnsanabrosgamedialog.h"
#pragma GCC diagnostic pop

ribi::QtNsanaBrosGameDialog::QtNsanaBrosGameDialog(
  const NsanaBrosOptions * const options,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtNsanaBrosGameDialog),
    m_game(new NsanaBrosGame),
    m_timer{}
{
  TRACE_FUNC();
  ui->setupUi(this);

  if (!options) return;

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
        m_game->GetKeys().get());
    ui->layout->addWidget(widget);
  }

  QObject::connect(&m_timer,&QTimer::timeout, //SxIGNAL(timeout()),
    this,&ribi::QtNsanaBrosGameDialog::OnTimerQt // SxLOT(OnTimerQt())
  );
  m_timer.setInterval(50);
  m_timer.start();
}

ribi::QtNsanaBrosGameDialog::~QtNsanaBrosGameDialog() noexcept
{
  delete ui;
}

void ribi::QtNsanaBrosGameDialog::keyPressEvent(QKeyEvent * e)
{
  m_game->KeyPress(e->key());
}

void ribi::QtNsanaBrosGameDialog::keyReleaseEvent(QKeyEvent * e)
{
  m_game->KeyRelease(e->key());
}

void ribi::QtNsanaBrosGameDialog::OnTimerQt()
{
  m_game->OnTimer();
}

