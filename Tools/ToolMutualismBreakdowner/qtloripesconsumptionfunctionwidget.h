#ifndef QTLORIPESCONSUMPTIONFUNCTIONWIDGET_H
#define QTLORIPESCONSUMPTIONFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtLoripesConsumptionFunctionWidget;
}

struct LoripesConsumptionFunction;


class QtLoripesConsumptionFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtLoripesConsumptionFunctionWidget(QWidget *parent = 0);
  ~QtLoripesConsumptionFunctionWidget();
  std::shared_ptr<LoripesConsumptionFunction> GetFunction() const noexcept;
  void SetFunction(const std::shared_ptr<LoripesConsumptionFunction>& f) noexcept;

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtLoripesConsumptionFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

#endif // QTLORIPESCONSUMPTIONFUNCTIONWIDGET_H
