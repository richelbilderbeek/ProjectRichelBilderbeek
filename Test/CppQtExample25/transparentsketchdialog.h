#ifndef TRANSPARENTSKETCHDIALOG_H
#define TRANSPARENTSKETCHDIALOG_H

#include <QDialog>

namespace Ui {
  class TransparentSketchDialog;
}

class TransparentSketchDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TransparentSketchDialog(QWidget *parent = 0);
  ~TransparentSketchDialog();

protected:
  void changeEvent(QEvent *e);
  void paintEvent(QPaintEvent *);

private:
  Ui::TransparentSketchDialog *ui;
  QPixmap m_pixmap;
};

#endif // TRANSPARENTSKETCHDIALOG_H
