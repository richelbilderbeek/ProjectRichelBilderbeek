#ifndef TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H
#define TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
class QtTestGraphicsProxyWidgetMainDialog;
}

class QtTestGraphicsProxyWidgetMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtTestGraphicsProxyWidgetMainDialog(QWidget *parent = 0);
    QtTestGraphicsProxyWidgetMainDialog(const QtTestGraphicsProxyWidgetMainDialog&) = delete;
    QtTestGraphicsProxyWidgetMainDialog& operator=(const QtTestGraphicsProxyWidgetMainDialog&) = delete;
    ~QtTestGraphicsProxyWidgetMainDialog() noexcept;
    
private:
    Ui::QtTestGraphicsProxyWidgetMainDialog *ui;
};

#endif // TOOLTESTGRAPHICSPROXYWIDGETMAINDIALOG_H
