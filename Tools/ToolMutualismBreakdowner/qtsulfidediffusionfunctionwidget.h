#ifndef QTSULFIDEDIFFUSIONFUNCTIONWIDGET_H
#define QTSULFIDEDIFFUSIONFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtSulfideDiffusionFunctionWidget;
}

namespace ribi {
namespace mb {

struct SulfideDiffusionFunction;

class QtSulfideDiffusionFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtSulfideDiffusionFunctionWidget(QWidget *parent = 0);
  ~QtSulfideDiffusionFunctionWidget();
  std::shared_ptr<SulfideDiffusionFunction> GetFunction() const noexcept;
  void SetFunction(const std::shared_ptr<SulfideDiffusionFunction>& f) noexcept;

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtSulfideDiffusionFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

} //~namespace mb
} //~namespace ribi

#endif // QTSULFIDEDIFFUSIONFUNCTIONWIDGET_H
