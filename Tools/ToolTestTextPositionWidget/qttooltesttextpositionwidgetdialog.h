#ifndef TOOLTESTTEXTPOSITIONWIDGETDIALOG_H
#define TOOLTESTTEXTPOSITIONWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolTestTextPositionWidgetDialog;
}

class QtToolTestTextPositionWidgetDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit QtToolTestTextPositionWidgetDialog(QWidget *parent = 0);
  QtToolTestTextPositionWidgetDialog(const QtToolTestTextPositionWidgetDialog&) = delete;
  QtToolTestTextPositionWidgetDialog& operator = (const QtToolTestTextPositionWidgetDialog&) = delete;
  ~QtToolTestTextPositionWidgetDialog() noexcept;
    
private:
  Ui::QtToolTestTextPositionWidgetDialog *ui;
};

#endif // TOOLTESTTEXTPOSITIONWIDGETDIALOG_H
