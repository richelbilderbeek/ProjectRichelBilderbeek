#ifndef QTDIALOG_H
#define QTDIALOG_H

#include "parameters.h"
#include <QDialog>

struct QwtPlotCurve;

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  Parameters GetParameters() const noexcept;

private slots:
  void Run();

private:
  Ui::QtDialog *ui;

  QwtPlotCurve * const m_curve_seagrass_density;
  QwtPlotCurve * const m_curve_sulfide_concentration;
  QwtPlotCurve * const m_curve_oxygen_concentration;
};

#endif // QTDIALOG_H
