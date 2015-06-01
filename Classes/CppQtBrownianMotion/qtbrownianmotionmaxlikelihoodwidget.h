#ifndef QTBROWNIANMOTIONMAXLIKELIHOODWIDGET_H
#define QTBROWNIANMOTIONMAXLIKELIHOODWIDGET_H

#include <QWidget>

namespace Ui {
class QtBrownianMotionMaxLikelihoodWidget;
}

class QtBrownianMotionMaxLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBrownianMotionMaxLikelihoodWidget(QWidget *parent = 0);
  ~QtBrownianMotionMaxLikelihoodWidget();

  double GetMaxLogLikelihood() const noexcept { return m_max_log_likelihood; }
  void SetData(const std::vector<double>& v);

private:
  Ui::QtBrownianMotionMaxLikelihoodWidget *ui;
  double m_max_log_likelihood;
};

#endif // QTBROWNIANMOTIONMAXLIKELIHOODWIDGET_H
