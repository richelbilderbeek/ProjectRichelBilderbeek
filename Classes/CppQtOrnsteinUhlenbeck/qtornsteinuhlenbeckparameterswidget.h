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

  void CalcLikelihood(
    const std::vector<double>& v
  ) noexcept;

  double GetInitValue() const noexcept;
  double GetTimestep() const noexcept;
  double GetEndTime() const noexcept;
  double GetLambda() const noexcept;
  double GetMu() const noexcept;
  double GetSigma() const noexcept;
  int GetSeed() const noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtOrnsteinUhlenbeckParametersWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTORNSTEINUHLENBECKPARAMETERSWIDGET_H
