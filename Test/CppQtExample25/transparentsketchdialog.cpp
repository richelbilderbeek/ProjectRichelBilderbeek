#include <QDesktopWidget>
#include <QPainter>
#include <QPixmap>
#include "transparentsketchdialog.h"
#include "ui_transparentsketchdialog.h"

TransparentSketchDialog::TransparentSketchDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::TransparentSketchDialog),
    m_pixmap(QPixmap::grabWindow(QApplication::desktop()->winId()))
{
  ui->setupUi(this);
}

TransparentSketchDialog::~TransparentSketchDialog()
{
  delete ui;
}

void TransparentSketchDialog::changeEvent(QEvent *e)
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

void TransparentSketchDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    m_pixmap,
    this->geometry());
}


