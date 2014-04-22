#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QBitmap>
#include <QPainter>
#include "transparentdialog.h"
#include "ui_transparentdialog.h"
#pragma GCC diagnostic pop

TransparentDialog::TransparentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransparentDialog)
{
  ui->setupUi(this);
}

TransparentDialog::~TransparentDialog()
{
  delete ui;
}

void TransparentDialog::resizeEvent(QResizeEvent *)
{
  //Make all transparent, except for the label
  QRegion maskedRegion(ui->label->geometry());
  setMask(maskedRegion);
}

