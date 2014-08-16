#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtvisualabcchordsdialog.h"
#include "ui_qtvisualabcchordsdialog.h"
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
