#ifndef QTSTOCHASTICITYINSPECTORSUPPORTWIDGET_H
#define QTSTOCHASTICITYINSPECTORSUPPORTWIDGET_H

#include <QWidget>

namespace Ui {
class QtStochasticityInspectorSupportWidget;
}

class QtStochasticityInspectorSupportWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtStochasticityInspectorSupportWidget(QWidget *parent = 0);
  ~QtStochasticityInspectorSupportWidget();

  void ShowSupport(const double log_likelihood_bm, const double log_likelihood_ou);

private:
  Ui::QtStochasticityInspectorSupportWidget *ui;

  double m_critical_value;
  double m_delta;

private slots:
  void OnChiChanged();
};

#endif // QTSTOCHASTICITYINSPECTORSUPPORTWIDGET_H
