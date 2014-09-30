#include "qtsimtoppredatorpraymaindialog.h"

#include <cassert>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QTimer>
#include "ui_qtsimtoppredatorpraymaindialog.h"

#include "qtsimtoppredatorpreywidget.h"

QtSimTopPredatorPrayMainDialog::QtSimTopPredatorPrayMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSimTopPredatorPrayMainDialog),
    m_widget_prey{new SimTopPredatorPreyWidget},
    m_widget_pred{new SimTopPredatorPreyWidget},
    m_widget_top{new SimTopPredatorPreyWidget}
{
  ui->setupUi(this);
  this->setGeometry(0,
    0,
    24 + (3 * SimTopPredatorPreyWidget::GetWidth()),
    16 + SimTopPredatorPreyWidget::GetHeight()
  );
  assert(!this->layout());
  QLayout * const layout = new QHBoxLayout;
  this->setLayout(layout);
  layout->addWidget(m_widget_prey);
  layout->addWidget(m_widget_pred);
  layout->addWidget(m_widget_top);

  //Put dialog at screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
  }
  QTimer * const timer{new QTimer(this)};
  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
  timer->setInterval(10);
  timer->start();
}

QtSimTopPredatorPrayMainDialog::~QtSimTopPredatorPrayMainDialog()
{
  delete ui;
}

void QtSimTopPredatorPrayMainDialog::OnTimer() noexcept
{
  static int z = 0;
  m_widget_prey->Set(z);
  m_widget_pred->Set(z+64);
  m_widget_top->Set(z+128);
  ++z;
}
