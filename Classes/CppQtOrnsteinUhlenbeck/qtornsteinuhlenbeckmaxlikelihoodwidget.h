#ifndef QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H
#define QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H

#include "ribi_time.h"
#include <QWidget>

namespace Ui {
class QtOrnsteinUhlenbeckMaxLikelihoodWidget;
}

class QtOrnsteinUhlenbeckMaxLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  using Time = ribi::units::Time;

  explicit QtOrnsteinUhlenbeckMaxLikelihoodWidget(QWidget *parent = 0);
  ~QtOrnsteinUhlenbeckMaxLikelihoodWidget();

  double GetMaxLogLikelihood() const noexcept { return m_max_log_likelihood; }
  void SetData(const std::vector<double>& v, const Time dt);

private:
  Ui::QtOrnsteinUhlenbeckMaxLikelihoodWidget *ui;
  double m_max_log_likelihood;
};

#endif // QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H
