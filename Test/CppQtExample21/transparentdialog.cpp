#include "transparentdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "ui_transparentdialog.h"
#pragma GCC diagnostic pop

TransparentDialog::TransparentDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::TransparentDialog),
    m_pixmap(QPixmap::grabWindow(QApplication::desktop()->winId()))
{
  ui->setupUi(this);
}

TransparentDialog::~TransparentDialog()
{
  delete ui;
}

void TransparentDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    m_pixmap,
    this->geometry());
}

