#ifndef QTORNSTEINUHLENBECKLIKELIHOODWIDGET_H
#define QTORNSTEINUHLENBECKLIKELIHOODWIDGET_H

#include <QWidget>

namespace Ui {
class QtOrnsteinUhlenbeckLikelihoodWidget;
}

class QtOrnsteinUhlenbeckLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtOrnsteinUhlenbeckLikelihoodWidget(QWidget *parent = 0);
  ~QtOrnsteinUhlenbeckLikelihoodWidget();

  void CalcLikelihood(
    const std::vector<double>& v,
    const double dt
  ) noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtOrnsteinUhlenbeckLikelihoodWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTORNSTEINUHLENBECKLIKELIHOODWIDGET_H
