//---------------------------------------------------------------------------
#include "sketchdialog.h"
#include "ui_sketchdialog.h"
//---------------------------------------------------------------------------
SketchDialog::SketchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SketchDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
SketchDialog::~SketchDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void SketchDialog::changeEvent(QEvent *e)
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

void SketchDialog::on_button_clear_clicked()
{
  ui->sketchwidget->clear();
}
