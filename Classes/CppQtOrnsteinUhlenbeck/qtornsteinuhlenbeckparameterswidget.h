#ifndef QTORNSTEINUHLENBECKPARAMETERSWIDGET_H
#define QTORNSTEINUHLENBECKPARAMETERSWIDGET_H

#include <QWidget>

namespace Ui {
class QtOrnsteinUhlenbeckParametersWidget;
}

class QtOrnsteinUhlenbeckParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtOrnsteinUhlenbeckParametersWidget(QWidget *parent = 0);
  ~QtOrnsteinUhlenbeckParametersWidget();

  double GetInitValue() const noexcept;
  double GetTimestep() const noexcept;
  double GetEndTime() const noexcept;

  ///mean reversion rate: theta on Wikipedia, lambda by van den Berg
  double GetMeanReversionRate() const noexcept;

  ///Target mean: mu
  double GetTargetMean() const noexcept;

  ///noise: sigma
  double GetVolatility() const noexcept;

  int GetSeed() const noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtOrnsteinUhlenbeckParametersWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTORNSTEINUHLENBECKPARAMETERSWIDGET_H
