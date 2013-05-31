#ifndef TOOLTESTTEXTPOSITIONWIDGETDIALOG_H
#define TOOLTESTTEXTPOSITIONWIDGETDIALOG_H

#include <QDialog>

namespace Ui {
class ToolTestTextPositionWidgetDialog;
}

class ToolTestTextPositionWidgetDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit ToolTestTextPositionWidgetDialog(QWidget *parent = 0);
  ~ToolTestTextPositionWidgetDialog();
    
private:
  Ui::ToolTestTextPositionWidgetDialog *ui;
};

#endif // TOOLTESTTEXTPOSITIONWIDGETDIALOG_H
