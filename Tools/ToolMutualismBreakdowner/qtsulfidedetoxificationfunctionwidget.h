#ifndef QTSULFIDEDETOXIFICATIONFUNCTIONWIDGET_H
#define QTSULFIDEDETOXIFICATIONFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtSulfideDetoxificationFunctionWidget;
}

namespace ribi {
namespace mb {

struct SulfideDetoxificationFunction;

class QtSulfideDetoxificationFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtSulfideDetoxificationFunctionWidget(QWidget *parent = 0);
  ~QtSulfideDetoxificationFunctionWidget();
  std::shared_ptr<SulfideDetoxificationFunction> GetFunction() const noexcept;
  void SetFunction(const std::shared_ptr<SulfideDetoxificationFunction>& f) noexcept;

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtSulfideDetoxificationFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

} //~namespace mb
} //~namespace ribi

#endif // QTSULFIDEDETOXIFICATIONFUNCTIONWIDGET_H
