#ifndef QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
#define QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H

#include "parameters.h"
#include <QWidget>

namespace Ui {
class QtMutualismBreakdownerParametersWidget;
}

class QtMutualismBreakdownerParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerParametersWidget(QWidget *parent = 0);
  ~QtMutualismBreakdownerParametersWidget();
  Parameters GetParameters() const noexcept;
  void SetParameters(const Parameters& parameters) noexcept;

private slots:

  void OnAnyChange();

  void on_button_set_random_values_clicked();
  void on_button_load_clicked();
  void on_button_save_clicked();

private:
  Ui::QtMutualismBreakdownerParametersWidget *ui;

  double GetRandom() const noexcept;
};

#endif // QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
