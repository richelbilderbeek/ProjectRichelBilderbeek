#ifndef QTBROWNIANMOTIONLIKELIHOODWIDGET_H
#define QTBROWNIANMOTIONLIKELIHOODWIDGET_H

#include <QWidget>

namespace Ui {
class QtBrownianMotionLikelihoodWidget;
}

class QtBrownianMotionLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBrownianMotionLikelihoodWidget(QWidget *parent = 0);
  ~QtBrownianMotionLikelihoodWidget();

private:
  Ui::QtBrownianMotionLikelihoodWidget *ui;
};

#endif // QTBROWNIANMOTIONLIKELIHOODWIDGET_H
