#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDesktopWidget>
#include <QPainter>
#include <QPixmap>
#include "transparentsketchdialog.h"
#include "ui_transparentsketchdialog.h"
#pragma GCC diagnostic pop

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

void TransparentSketchDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    m_pixmap,
    this->geometry()
  );
}


