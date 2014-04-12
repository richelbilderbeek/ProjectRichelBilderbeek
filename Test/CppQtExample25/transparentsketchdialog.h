#ifndef TRANSPARENTSKETCHDIALOG_H
#define TRANSPARENTSKETCHDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class TransparentSketchDialog;
}

class TransparentSketchDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TransparentSketchDialog(QWidget *parent = 0);
  TransparentSketchDialog(const TransparentSketchDialog&) = delete;
  TransparentSketchDialog& operator=(const TransparentSketchDialog&) = delete;
  ~TransparentSketchDialog();

protected:
  void paintEvent(QPaintEvent *);

private:
  Ui::TransparentSketchDialog *ui;
  QPixmap m_pixmap;
};

#endif // TRANSPARENTSKETCHDIALOG_H
