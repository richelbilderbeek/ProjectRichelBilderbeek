#include "pongdialog.h"

#include <QKeyEvent>

#include "ui_pongdialog.h"


PongDialog::PongDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PongDialog)
{
  ui->setupUi(this);
  this->startTimer(100);
}

PongDialog::~PongDialog()
{
  delete ui;
}

void PongDialog::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_A:
      ui->player_left->setGeometry(
        ui->player_left->geometry().translated(0,-1)
      );
    break;
  }
}

void PongDialog::timerEvent(QTimerEvent *)
{
  ui->player_right->setGeometry(
    ui->player_right->geometry().translated(0,1)
  );
}
