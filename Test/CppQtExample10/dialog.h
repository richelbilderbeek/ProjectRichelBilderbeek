#ifndef DIALOG_H
#define DIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  Dialog(const Dialog&) = delete;
  Dialog& operator=(const Dialog&) = delete;
  ~Dialog();

protected:
  void resizeEvent(QResizeEvent *e); //Added

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_H
