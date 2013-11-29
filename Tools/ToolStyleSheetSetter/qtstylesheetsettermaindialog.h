#ifndef TOOLSTYLESHEETSETTERMAINDIALOG_H
#define TOOLSTYLESHEETSETTERMAINDIALOG_H

#include <string>
#include "qthideandshowdialog.h"

namespace Ui {
  class QtStyleSheetSetterMainDialog;
}

namespace ribi {

class QtStyleSheetSetterMainDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtStyleSheetSetterMainDialog(const std::string& stylesheet = "", QWidget *parent = 0);
  QtStyleSheetSetterMainDialog(const QtStyleSheetSetterMainDialog&) = delete;
  QtStyleSheetSetterMainDialog& operator=(const QtStyleSheetSetterMainDialog&) = delete;
  ~QtStyleSheetSetterMainDialog() noexcept;
  const std::string& GetStyleSheet() const { return m_stylesheet; }

protected:
  void keyPressEvent(QKeyEvent * event);
    
private slots:
  void on_stylesheet_textChanged();

private:
  Ui::QtStyleSheetSetterMainDialog *ui;
  std::string m_stylesheet;
};

} //~namespace ribi

#endif // TOOLSTYLESHEETSETTERMAINDIALOG_H
