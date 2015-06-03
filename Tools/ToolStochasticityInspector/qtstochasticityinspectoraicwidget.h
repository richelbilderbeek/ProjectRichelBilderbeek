#ifndef QTSTOCHASTICITYINSPECTORAICWIDGET_H
#define QTSTOCHASTICITYINSPECTORAICWIDGET_H

#include "apfloat.h"
#include <QWidget>

namespace Ui {
class QtStochasticityInspectorAicWidget;
}

///Akaike Information Criterion widget
class QtStochasticityInspectorAicWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtStochasticityInspectorAicWidget(QWidget *parent = 0);
  ~QtStochasticityInspectorAicWidget();

  void ShowAic(const double log_likelihood_bm, const double log_likelihood_ou);

private:
  Ui::QtStochasticityInspectorAicWidget *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // QTSTOCHASTICITYINSPECTORAICWIDGET_H
