#ifndef SKETCHDIALOG_H
#define SKETCHDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class SketchDialog;
}

class SketchDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SketchDialog(QWidget *parent = 0);
  SketchDialog(const SketchDialog&) = delete;
  SketchDialog& operator=(const SketchDialog&) = delete;
  ~SketchDialog();

private:
  Ui::SketchDialog *ui;

private slots:
    void on_button_clear_clicked();
};

#endif // SKETCHDIALOG_H
