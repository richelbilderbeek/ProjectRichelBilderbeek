#ifndef QTFUNCTIONPLOTTERMENUDIALOG_H
#define QTFUNCTIONPLOTTERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtFunctionPlotterMenuDialog;
}

namespace ribi {

class QtFunctionPlotterMenuDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtFunctionPlotterMenuDialog(QWidget *parent = 0);
    QtFunctionPlotterMenuDialog(const QtFunctionPlotterMenuDialog&) = delete;
    QtFunctionPlotterMenuDialog& operator=(const QtFunctionPlotterMenuDialog&) = delete;
    ~QtFunctionPlotterMenuDialog() noexcept;
    
private slots:
    void on_button_start_clicked();
    void on_button_about_clicked();
    void on_button_quit_clicked();

private:
    Ui::QtFunctionPlotterMenuDialog *ui;
};

} //~namespace ribi

#endif // QTFUNCTIONPLOTTERMENUDIALOG_H
