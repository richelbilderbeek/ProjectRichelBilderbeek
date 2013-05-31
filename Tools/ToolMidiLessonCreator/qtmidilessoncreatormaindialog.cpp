#include "qtmidilessoncreatormaindialog.h"
#include "ui_qtmidilessoncreatormaindialog.h"

QtMidiLessonCreatorMainDialog::QtMidiLessonCreatorMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMidiLessonCreatorMainDialog)
{
  ui->setupUi(this);
}

QtMidiLessonCreatorMainDialog::~QtMidiLessonCreatorMainDialog()
{
  delete ui;
}
