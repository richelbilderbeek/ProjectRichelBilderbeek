#ifndef QTORNSTEINUHLENBECKPARAMETERSWIDGET_H
#define QTORNSTEINUHLENBECKPARAMETERSWIDGET_H

#include "rate.h"
#include "ribi_time.h"
#include <QWidget>

namespace Ui {
class QtOrnsteinUhlenbeckParametersWidget;
}

class QtOrnsteinUhlenbeckParametersWidget : public QWidget
{
  Q_OBJECT

public:
  using Rate = ribi::units::Rate;
  using Time = ribi::units::Time;

  explicit QtOrnsteinUhlenbeckParametersWidget(QWidget *parent = 0);
  ~QtOrnsteinUhlenbeckParametersWidget();

  double GetInitValue() const noexcept;
  Time GetTimestep() const noexcept;
  Time GetEndTime() const noexcept;

  ///mean reversion rate: theta on Wikipedia, lambda by van den Berg
  Rate GetMeanReversionRate() const noexcept;

  ///Target mean: mu
  double GetTargetMean() const noexcept;

  ///noise: sigma
  Rate GetVolatility() const noexcept;

  int GetSeed() const noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtOrnsteinUhlenbeckParametersWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTORNSTEINUHLENBECKPARAMETERSWIDGET_H
