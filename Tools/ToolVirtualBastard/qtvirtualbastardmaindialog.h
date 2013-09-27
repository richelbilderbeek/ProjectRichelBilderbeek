#ifndef QTVIRTUALBASTARDMAINDIALOG_H
#define QTVIRTUALBASTARDMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtVirtualBastardMainDialog;
}

class QtVirtualBastardMainDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtVirtualBastardMainDialog(QWidget *parent = 0);
  QtVirtualBastardMainDialog(const QtVirtualBastardMainDialog&) = delete;
  QtVirtualBastardMainDialog& operator=(const QtVirtualBastardMainDialog&) = delete;
  ~QtVirtualBastardMainDialog();
  
private slots:
  void on_button_clicked();

  void on_button_set_mouse_pos_clicked();

  void on_button_click_clicked();

  void on_button_get_pos_clicked();

private:
  Ui::QtVirtualBastardMainDialog *ui;

  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);
};

#endif // QTVIRTUALBASTARDMAINDIALOG_H
