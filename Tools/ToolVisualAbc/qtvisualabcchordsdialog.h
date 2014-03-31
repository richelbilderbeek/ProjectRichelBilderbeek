#ifndef QTTOOLVISUALABCCHORDSDIALOG_H
#define QTTOOLVISUALABCCHORDSDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtVisualAbcChordsDialog;
}

namespace ribi {

class QtVisualAbcChordsDialog : public QtHideAndShowDialog
{
    Q_OBJECT

public:
    explicit QtVisualAbcChordsDialog(QWidget *parent = 0);
    QtVisualAbcChordsDialog(const QtVisualAbcChordsDialog&) = delete;
    QtVisualAbcChordsDialog& operator=(const QtVisualAbcChordsDialog&) = delete;
    ~QtVisualAbcChordsDialog() noexcept;

private:
    Ui::QtVisualAbcChordsDialog *ui;
};

} //~namespace ribi

#endif // QTTOOLVISUALABCCHORDSDIALOG_H
