#ifndef QTSTOCHASTICITYINSPECTORHLRTWIDGET_H
#define QTSTOCHASTICITYINSPECTORHLRTWIDGET_H

#include "apfloat.h"
#include <QWidget>

namespace Ui {
class QtStochasticityInspectorHlrtWidget;
}

///Hierarchical Likelihood-Ratio Test
class QtStochasticityInspectorHlrtWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtStochasticityInspectorHlrtWidget(QWidget *parent = 0);
  ~QtStochasticityInspectorHlrtWidget();

  void ShowHlrt(const double log_likelihood_bm, const double log_likelihood_ou);

private:
  Ui::QtStochasticityInspectorHlrtWidget *ui;

  double m_critical_value;
  double m_delta;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnChiChanged();
};

#endif // QTSTOCHASTICITYINSPECTORHLRTWIDGET_H
