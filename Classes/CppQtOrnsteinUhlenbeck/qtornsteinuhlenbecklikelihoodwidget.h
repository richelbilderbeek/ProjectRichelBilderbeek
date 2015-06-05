#ifndef QTORNSTEINUHLENBECKLIKELIHOODWIDGET_H
#define QTORNSTEINUHLENBECKLIKELIHOODWIDGET_H

#include <QWidget>
#include "ribi_time.h"

namespace Ui {
  class QtOrnsteinUhlenbeckLikelihoodWidget;
}

class QtOrnsteinUhlenbeckLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  using Time = ribi::units::Time;

  explicit QtOrnsteinUhlenbeckLikelihoodWidget(QWidget *parent = 0);
  ~QtOrnsteinUhlenbeckLikelihoodWidget();

  void CalcLikelihood(
    const std::vector<double>& v,
    const Time dt
  ) noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtOrnsteinUhlenbeckLikelihoodWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTORNSTEINUHLENBECKLIKELIHOODWIDGET_H
