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

  void CalcMaxLikelihood(const std::vector<double>& v, const double dt);

private:
  Ui::QtOrnsteinUhlenbeckMaxLikelihoodWidget *ui;
};

#endif // QTORNSTEINUHLENBECKMAXLIKELIHOODWIDGET_H
