#ifndef QTSULFIDEPRODUCTIONFUNCTIONWIDGET_H
#define QTSULFIDEPRODUCTIONFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtSulfideProductionFunctionWidget;
}

struct SulfideProductionFunction;


class QtSulfideProductionFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtSulfideProductionFunctionWidget(QWidget *parent = 0);
  ~QtSulfideProductionFunctionWidget();
  std::shared_ptr<SulfideProductionFunction> GetFunction() const noexcept;
  void SetFunction(const std::shared_ptr<SulfideProductionFunction>& f) noexcept;

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtSulfideProductionFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

#endif // QTSULFIDEPRODUCTIONFUNCTIONWIDGET_H
