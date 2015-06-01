#ifndef QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H
#define QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H

#include <QWidget>

namespace Ui {
class QtOrnsteinUhlenbeckMaxLikelihoodWidget;
}

class QtOrnsteinUhlenbeckMaxLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtOrnsteinUhlenbeckMaxLikelihoodWidget(QWidget *parent = 0);
  ~QtOrnsteinUhlenbeckMaxLikelihoodWidget();

  double GetMaxLogLikelihood() const noexcept { return m_max_log_likelihood; }
  void SetData(const std::vector<double>& v, const double dt);

private:
  Ui::QtOrnsteinUhlenbeckMaxLikelihoodWidget *ui;
  double m_max_log_likelihood;
};

#endif // QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H
