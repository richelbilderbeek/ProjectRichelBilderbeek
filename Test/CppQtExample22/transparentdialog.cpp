#include <QBitmap>
#include <QPainter>
#include "transparentdialog.h"
#include "ui_transparentdialog.h"
//---------------------------------------------------------------------------
TransparentDialog::TransparentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransparentDialog)
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
void TransparentDialog::resizeEvent(QResizeEvent *)
{
  //Make all transparent, except for the label
  QRegion maskedRegion(ui->label->geometry());
  setMask(maskedRegion);
}
//---------------------------------------------------------------------------
