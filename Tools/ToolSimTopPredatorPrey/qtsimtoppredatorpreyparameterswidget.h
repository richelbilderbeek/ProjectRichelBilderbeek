#ifndef QTSIMTOPPREDATORPREYPARAMETERSWIDGET_H
#define QTSIMTOPPREDATORPREYPARAMETERSWIDGET_H

#include <QDialog>

namespace Ui {
class QtSimTopPredatorPreyParametersWidget;
}

class QtSimTopPredatorPreyParametersWidget : public QDialog
{
  Q_OBJECT

public:
  explicit QtSimTopPredatorPreyParametersWidget(QWidget *parent = 0);
  QtSimTopPredatorPreyParametersWidget(const QtSimTopPredatorPreyParametersWidget&) = delete;
  QtSimTopPredatorPreyParametersWidget& operator=(const QtSimTopPredatorPreyParametersWidget&) = delete;
  ~QtSimTopPredatorPreyParametersWidget();

  double GetConvPredToTop() const noexcept;
  double GetConvPreyToPred() const noexcept;

  double GetDiffusionPred() const noexcept;
  double GetDiffusionPrey() const noexcept;
  double GetDiffusionTop() const noexcept;


  double GetFractionPred() const noexcept;
  double GetFractionPrey() const noexcept;
  double GetFractionTop() const noexcept;

  double GetHuntEffPred() const noexcept;
  double GetHuntEffTop() const noexcept;

  //Hide the top-predator page, so it can be used in a predator-prey system
  void HideTopPredator();

signals:
  void signal_parameters_changed();

private slots:
  void OnAnyChange();

private:
  Ui::QtSimTopPredatorPreyParametersWidget *ui;
};

#endif // QTSIMTOPPREDATORPREYPARAMETERSWIDGET_H
