#ifndef QTSECRETMESSAGEEXTRACTDIALOG_H
#define QTSECRETMESSAGEEXTRACTDIALOG_H

#include "qthideandshowdialog.h"


namespace Ui {
  class QtSecretMessageExtractDialog;
}

namespace ribi {
namespace sema {

class QtSecretMessageExtractDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtSecretMessageExtractDialog(QWidget *parent = 0);
    QtSecretMessageExtractDialog(const QtSecretMessageExtractDialog&) = delete;
    QtSecretMessageExtractDialog& operator=(const QtSecretMessageExtractDialog&) = delete;
    ~QtSecretMessageExtractDialog() noexcept;
    
private slots:
    void on_button_load_clicked();

private:
    Ui::QtSecretMessageExtractDialog *ui;
};

} //~namespace sema
} //~namespace ribi

#endif // QTSECRETMESSAGEEXTRACTDIALOG_H
