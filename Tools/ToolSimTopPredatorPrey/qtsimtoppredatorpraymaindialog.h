#ifndef QTSIMTOPPREDATORPRAYMAINDIALOG_H
#define QTSIMTOPPREDATORPRAYMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSimTopPredatorPrayMainDialog;
}

struct SimTopPredatorPreyWidget;

class QtSimTopPredatorPrayMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtSimTopPredatorPrayMainDialog(QWidget *parent = 0);
  ~QtSimTopPredatorPrayMainDialog();

private:
  Ui::QtSimTopPredatorPrayMainDialog *ui;
  SimTopPredatorPreyWidget * const m_widget_prey;
  SimTopPredatorPreyWidget * const m_widget_pred;
  SimTopPredatorPreyWidget * const m_widget_top;

private slots:
  void OnTimer() noexcept;
};

#endif // QTSIMTOPPREDATORPRAYMAINDIALOG_H
