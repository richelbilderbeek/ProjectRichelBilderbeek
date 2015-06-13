#ifndef QTSULFIDECONSUMPTIONFUNCTIONWIDGET_H
#define QTSULFIDECONSUMPTIONFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtSulfideConsumptionFunctionWidget;
}

namespace ribi {
namespace mb {

struct SulfideConsumptionFunction;

class QtSulfideConsumptionFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtSulfideConsumptionFunctionWidget(QWidget *parent = 0);
  ~QtSulfideConsumptionFunctionWidget();
  std::shared_ptr<SulfideConsumptionFunction> GetFunction() const noexcept;
  void SetFunction(const std::shared_ptr<SulfideConsumptionFunction>& f) noexcept;

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtSulfideConsumptionFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

} //~namespace mb
} //~namespace ribi

#endif // QTSULFIDECONSUMPTIONFUNCTIONWIDGET_H
