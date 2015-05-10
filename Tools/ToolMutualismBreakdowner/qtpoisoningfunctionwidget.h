#ifndef QTPOISONINGFUNCTIONWIDGET_H
#define QTPOISONINGFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtPoisoningFunctionWidget;
}

struct PoisoningFunction;


class QtPoisoningFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtPoisoningFunctionWidget(QWidget *parent = 0);
  ~QtPoisoningFunctionWidget();
  std::shared_ptr<PoisoningFunction> GetFunction() const noexcept;
  void SetFunction(const std::shared_ptr<PoisoningFunction>& f) noexcept;

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtPoisoningFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

#endif // QTPOISONINGFUNCTIONWIDGET_H
