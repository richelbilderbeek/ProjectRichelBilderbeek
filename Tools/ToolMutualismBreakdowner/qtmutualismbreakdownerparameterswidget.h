#ifndef QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
#define QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H

#include "parameters.h"
#include <QWidget>

namespace Ui {
  class QtMutualismBreakdownerParametersWidget;
}

struct QtPoisoningFunctionWidget;
struct QtSeagrassGrowthFunctionWidget;
struct QtSulfideConsumptionFunctionWidget;
struct QtSulfideDetoxificationFunctionWidget;
struct QtSulfideDiffusionFunctionWidget;
struct QtSulfideProductionFunctionWidget;

class QtMutualismBreakdownerParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerParametersWidget(QWidget *parent = 0);
  ~QtMutualismBreakdownerParametersWidget();
  Parameters GetParameters() const;
  void SetParameters(const Parameters& parameters);

signals:
  void signal_parameters_changed() const;


private slots:

  void OnAnyChange();

  void on_button_set_random_values_clicked();
  void on_button_load_clicked();
  void on_button_save_clicked();

private:
  Ui::QtMutualismBreakdownerParametersWidget *ui;

  QtPoisoningFunctionWidget * const m_qtpoisoningwidget;
  QtSeagrassGrowthFunctionWidget * const m_qtseagrassgrowthwidget;
  QtSulfideConsumptionFunctionWidget * const m_qtsulfideconsumptionwidget;
  QtSulfideDetoxificationFunctionWidget * const m_qtsulfidedetoxificationwidget;
  QtSulfideDiffusionFunctionWidget * const m_qtsulfidediffusionwidget;
  QtSulfideProductionFunctionWidget * const m_qtsulfideproductionwidget;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
