#ifndef QTSECRETMESSAGEEXTRACTDIALOG_H
#define QTSECRETMESSAGEEXTRACTDIALOG_H

#include "qthideandshowdialog.h"


namespace Ui {
  class QtSecretMessageExtractDialog2;
}

namespace ribi {
namespace sema {

class QtSecretMessageExtractDialog2 : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtSecretMessageExtractDialog2(QWidget *parent = 0);
    QtSecretMessageExtractDialog2(const QtSecretMessageExtractDialog2&) = delete;
    QtSecretMessageExtractDialog2& operator=(const QtSecretMessageExtractDialog2&) = delete;
    ~QtSecretMessageExtractDialog2() noexcept;
    
private slots:
    void on_button_load_clicked();

private:
    Ui::QtSecretMessageExtractDialog2 *ui;
};

} //~namespace sema
} //~namespace ribi

#endif // QTSECRETMESSAGEEXTRACTDIALOG_H
