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

  void CalcLikelihood(const std::vector<double>& v) noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtBrownianMotionLikelihoodWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTBROWNIANMOTIONLIKELIHOODWIDGET_H
