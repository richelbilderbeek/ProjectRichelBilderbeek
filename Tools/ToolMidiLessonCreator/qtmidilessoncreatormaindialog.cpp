#include "qtmidilessoncreatormaindialog.h"
#include "ui_qtmidilessoncreatormaindialog.h"

ribi::QtMidiLessonCreatorMainDialog::QtMidiLessonCreatorMainDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtMidiLessonCreatorMainDialog)
{
  ui->setupUi(this);
}

ribi::QtMidiLessonCreatorMainDialog::~QtMidiLessonCreatorMainDialog()
{
  delete ui;
}
