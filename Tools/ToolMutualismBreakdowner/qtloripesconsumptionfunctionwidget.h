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

private:
  Ui::QtLoripesConsumptionFunctionWidget *ui;
};

#endif // QTLORIPESCONSUMPTIONFUNCTIONWIDGET_H
