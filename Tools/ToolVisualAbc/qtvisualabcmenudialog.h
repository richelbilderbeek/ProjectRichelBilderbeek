#ifndef QTVISUALABCMENUDIALOG_H
#define QTVISUALABCMENUDIALOG_H

#include <QDialog>

namespace Ui {
  class QtVisualAbcMenuDialog;
}

class QtVisualAbcMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtVisualAbcMenuDialog(QWidget *parent = 0);
  ~QtVisualAbcMenuDialog();

private:
  Ui::QtVisualAbcMenuDialog *ui;

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_start_clicked();
};

#endif // QTVISUALABCMENUDIALOG_H
