#ifndef QTSEAGRASSGROWTHFUNCTIONWIDGET_H
#define QTSEAGRASSGROWTHFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtSeagrassGrowthFunctionWidget;
}

struct SeagrassGrowthFunction;


class QtSeagrassGrowthFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtSeagrassGrowthFunctionWidget(QWidget *parent = 0);
  ~QtSeagrassGrowthFunctionWidget();
  std::shared_ptr<SeagrassGrowthFunction> GetFunction() const;
  void SetFunction(const std::shared_ptr<SeagrassGrowthFunction>& f);

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtSeagrassGrowthFunctionWidget *ui;

  #ifndef NDEBUG
  //static void Test() noexcept;
  #endif

private slots:
  void OnAnyChange();
};

#endif // QTSEAGRASSGROWTHFUNCTIONWIDGET_H
