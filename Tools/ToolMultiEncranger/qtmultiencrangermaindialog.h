#ifndef QTTOOLMULTIENCRANGERDIALOG_H
#define QTTOOLMULTIENCRANGERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolMultiEncrangerMainDialog;
}

namespace ribi {

struct ToolMultiEncrangerMainDialog;

class QtToolMultiEncrangerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolMultiEncrangerMainDialog(QWidget *parent = 0) noexcept;
  QtToolMultiEncrangerMainDialog(const QtToolMultiEncrangerMainDialog&) = delete;
  QtToolMultiEncrangerMainDialog& operator=(const QtToolMultiEncrangerMainDialog&) = delete;
  ~QtToolMultiEncrangerMainDialog() noexcept;

protected:

private:
  Ui::QtToolMultiEncrangerMainDialog *ui;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  ToolMultiEncrangerMainDialog * const m_dialog;

private slots:
  void on_button_deencrypt_clicked() noexcept;
  void on_button_encrypt_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLMULTIENCRANGERDIALOG_H
