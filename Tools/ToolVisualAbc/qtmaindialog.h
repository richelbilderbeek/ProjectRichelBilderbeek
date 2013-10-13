#ifndef QTVISUALABCMAINDIALOG_H
#define QTVISUALABCMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtMainDialog;
}

class QtMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtMainDialog(QWidget *parent = 0);
  ~QtMainDialog();

private:
  Ui::QtMainDialog *ui;
  void resizeEvent(QResizeEvent *);

private slots:
    void on_label_save_clicked();
    void on_button_play_clicked();
    void on_button_convert_clicked();
};

#endif // QTVISUALABCMAINDIALOG_H
