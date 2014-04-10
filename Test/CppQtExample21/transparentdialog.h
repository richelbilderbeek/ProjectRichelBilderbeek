#ifndef TRANSPARENTDIALOG_H
#define TRANSPARENTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class TransparentDialog;
}

class TransparentDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TransparentDialog(QWidget *parent = 0);
  TransparentDialog(const TransparentDialog&) = delete;
  TransparentDialog& operator=(const TransparentDialog&) = delete;
  ~TransparentDialog();

protected:
  void paintEvent(QPaintEvent *);

private:
  Ui::TransparentDialog *ui;
  QPixmap m_pixmap;

private slots:
};

#endif // TRANSPARENTDIALOG_H
