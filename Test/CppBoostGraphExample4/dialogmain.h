
#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H

#include <QDialog>

namespace Ui {
  class DialogMain;
}

class DialogMain : public QDialog
{
  Q_OBJECT

public:
  explicit DialogMain(QWidget *parent = 0);
  ~DialogMain();

private:
  Ui::DialogMain *ui;
};

#endif // DIALOGMAIN_H
