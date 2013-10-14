#include "dialog.h"

#include <QScrollBar>
#include <QTimer>

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog),
  m_timer(new QTimer)
{
  ui->setupUi(this);
  ui->listWidget->setAlternatingRowColors(true);
  ui->listWidget->setWordWrap(true);

  QObject::connect(m_timer,&QTimer::timeout,this,&Dialog::OnTimer);
  m_timer->setInterval(1);
  m_timer->start();
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_pushButton_clicked()
{
  QListWidgetItem * const item = new QListWidgetItem;
  item->setText("0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789");
  ui->listWidget->addItem(item);
  this->repaint();
  m_timer->start();
}

void Dialog::OnTimer()
{
  if (ui->listWidget->verticalScrollBar()->isVisible())
  {
    const int height = ui->listWidget->height();
    ui->listWidget->setMinimumHeight(height + 1);
  }
  else
  {
    m_timer->stop();
  }
}
