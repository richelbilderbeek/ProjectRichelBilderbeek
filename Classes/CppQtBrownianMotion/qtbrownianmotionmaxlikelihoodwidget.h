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

  void CalcMaxLikelihood(const std::vector<double>& v);

private:
  Ui::QtBrownianMotionMaxLikelihoodWidget *ui;
};

#endif // QTBROWNIANMOTIONMAXLIKELIHOODWIDGET_H
