#ifndef QTLIZARDPAPERROCKSCISSORSSPOCKMAINDIALOG_H
#define QTLIZARDPAPERROCKSCISSORSSPOCKMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtLizardPaperRockScissorsSpockMainDialog;
}

struct QtLizardPaperRockScissorsSpockWidget;

class QtLizardPaperRockScissorsSpockMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtLizardPaperRockScissorsSpockMainDialog(QWidget *parent = 0);
  QtLizardPaperRockScissorsSpockMainDialog(const QtLizardPaperRockScissorsSpockMainDialog&) = delete;
  QtLizardPaperRockScissorsSpockMainDialog& operator=(const QtLizardPaperRockScissorsSpockMainDialog&) = delete;
  ~QtLizardPaperRockScissorsSpockMainDialog();

private slots:
  void OnAnyChange();

private:
  Ui::QtLizardPaperRockScissorsSpockMainDialog *ui;
  QtLizardPaperRockScissorsSpockWidget * const m_widget;
};

#endif // QTLIZARDPAPERROCKSCISSORSSPOCKMAINDIALOG_H
