#ifndef QTBROWNIANMOTIONPARAMETERSWIDGET_H
#define QTBROWNIANMOTIONPARAMETERSWIDGET_H

#include <QWidget>

namespace Ui {
class QtBrownianMotionParametersWidget;
}

class QtBrownianMotionParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBrownianMotionParametersWidget(QWidget *parent = 0);
  ~QtBrownianMotionParametersWidget();



  double GetInitValue() const noexcept;
  int GetEndTime() const noexcept;

  ///noise: sigma
  double GetVolatility() const noexcept;

  int GetSeed() const noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtBrownianMotionParametersWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTBROWNIANMOTIONPARAMETERSWIDGET_H
