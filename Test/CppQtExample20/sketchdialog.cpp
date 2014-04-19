#include "sketchdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "ui_sketchdialog.h"
#pragma GCC diagnostic pop

SketchDialog::SketchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SketchDialog)
{
  ui->setupUi(this);
}

SketchDialog::~SketchDialog()
{
  delete ui;
}

void SketchDialog::on_button_clear_clicked()
{
  ui->sketchwidget->clear();
}
