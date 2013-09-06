#ifndef TOOLSTYLESHEETSETTERMAINDIALOG_H
#define TOOLSTYLESHEETSETTERMAINDIALOG_H

#include <string>
#include "qthideandshowdialog.h"

namespace Ui {
class ToolStyleSheetSetterMainDialog;
}

class ToolStyleSheetSetterMainDialog : public ribi::QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit ToolStyleSheetSetterMainDialog(const std::string& stylesheet = "", QWidget *parent = 0);
  ~ToolStyleSheetSetterMainDialog();
  const std::string& GetStyleSheet() const { return m_stylesheet; }

protected:
  void keyPressEvent(QKeyEvent * event);
    
private slots:
  void on_stylesheet_textChanged();

private:
  Ui::ToolStyleSheetSetterMainDialog *ui;
  std::string m_stylesheet;
};

#endif // TOOLSTYLESHEETSETTERMAINDIALOG_H
