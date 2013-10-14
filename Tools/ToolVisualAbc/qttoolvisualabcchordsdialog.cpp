#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttoolvisualabcchordsdialog.h"
#include "ui_qttoolvisualabcchordsdialog.h"
#pragma GCC diagnostic pop

ribi::QtVisualAbcChordsDialog::QtVisualAbcChordsDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtVisualAbcChordsDialog)
{
    ui->setupUi(this);
}

ribi::QtVisualAbcChordsDialog::~QtVisualAbcChordsDialog() noexcept
{
    delete ui;
}
