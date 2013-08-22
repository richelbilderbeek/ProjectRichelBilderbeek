//---------------------------------------------------------------------------
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "transparentdialog.h"
#include "ui_transparentdialog.h"
//---------------------------------------------------------------------------
TransparentDialog::TransparentDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::TransparentDialog),
    m_pixmap(QPixmap::grabWindow(QApplication::desktop()->winId()))
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
TransparentDialog::~TransparentDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void TransparentDialog::changeEvent(QEvent *e)
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
void TransparentDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    m_pixmap,
    this->geometry());
}
//---------------------------------------------------------------------------
