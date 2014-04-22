#ifndef TOOLTESTTEXTPOSITIONWIDGETDIALOG_H
#define TOOLTESTTEXTPOSITIONWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

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
