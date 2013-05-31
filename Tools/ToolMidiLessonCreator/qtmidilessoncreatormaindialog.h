#ifndef QTMIDILESSONCREATORMAINDIALOG_H
#define QTMIDILESSONCREATORMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtMidiLessonCreatorMainDialog;
}

class QtMidiLessonCreatorMainDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtMidiLessonCreatorMainDialog(QWidget *parent = 0);
  ~QtMidiLessonCreatorMainDialog();
  
private:
  Ui::QtMidiLessonCreatorMainDialog *ui;
};

#endif // QTMIDILESSONCREATORMAINDIALOG_H
