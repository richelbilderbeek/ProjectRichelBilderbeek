#ifndef TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H
#define TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
class ToolTestGraphicsProxyWidgetMainDialog;
}

class ToolTestGraphicsProxyWidgetMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ToolTestGraphicsProxyWidgetMainDialog(QWidget *parent = 0);
    ToolTestGraphicsProxyWidgetMainDialog(const ToolTestGraphicsProxyWidgetMainDialog&) = delete;
    ToolTestGraphicsProxyWidgetMainDialog& operator=(const ToolTestGraphicsProxyWidgetMainDialog&) = delete;
    ~ToolTestGraphicsProxyWidgetMainDialog() noexcept;
    
private:
    Ui::ToolTestGraphicsProxyWidgetMainDialog *ui;
};

#endif // TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H
