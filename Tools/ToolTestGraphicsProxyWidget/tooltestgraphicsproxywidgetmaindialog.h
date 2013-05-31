#ifndef TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H
#define TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H

#include <QDialog>

namespace Ui {
class ToolTestGraphicsProxyWidgetMainDialog;
}

class ToolTestGraphicsProxyWidgetMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ToolTestGraphicsProxyWidgetMainDialog(QWidget *parent = 0);
    ~ToolTestGraphicsProxyWidgetMainDialog();
    
private:
    Ui::ToolTestGraphicsProxyWidgetMainDialog *ui;
};

#endif // TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H
