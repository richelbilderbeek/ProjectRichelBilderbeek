#ifndef QTVALENTINECARDDECRYPTERMAINDIALOG_H
#define QTVALENTINECARDDECRYPTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#include <QImage>
#pragma GCC diagnostic pop

namespace Ui {
  class QtValentineCardDecrypterMainDialog;
}

struct QLabel;

namespace ribi {

class QtValentineCardDecrypterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtValentineCardDecrypterMainDialog(QWidget *parent = 0);
  QtValentineCardDecrypterMainDialog(const QtValentineCardDecrypterMainDialog&) = delete;
  QtValentineCardDecrypterMainDialog& operator=(const QtValentineCardDecrypterMainDialog&) = delete;
  ~QtValentineCardDecrypterMainDialog() noexcept;

private slots:

  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtValentineCardDecrypterMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTVALENTINECARDDECRYPTERMAINDIALOG_H
