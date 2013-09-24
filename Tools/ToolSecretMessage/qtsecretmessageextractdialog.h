#ifndef QTSECRETMESSAGEEXTRACTDIALOG_H
#define QTSECRETMESSAGEEXTRACTDIALOG_H

#include "qthideandshowdialog.h"


namespace Ui {
  class QtSecretMessageExtractDialog;
}

namespace ribi {

class QtSecretMessageExtractDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtSecretMessageExtractDialog(QWidget *parent = 0);
    QtSecretMessageExtractDialog(const QtSecretMessageExtractDialog&) = delete;
    QtSecretMessageExtractDialog& operator=(const QtSecretMessageExtractDialog&) = delete;
    ~QtSecretMessageExtractDialog() noexcept;
    
private:
    Ui::QtSecretMessageExtractDialog *ui;
};

} //~namespace ribi

#endif // QTSECRETMESSAGEEXTRACTDIALOG_H
