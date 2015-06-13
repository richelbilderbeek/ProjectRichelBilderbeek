#ifndef QTSEAGRASSCOLONISATIONFUNCTIONWIDGET_H
#define QTSEAGRASSCOLONISATIONFUNCTIONWIDGET_H

#include <memory>
#include <QWidget>

namespace Ui {
  class QtSeagrassColonisationFunctionWidget;
}

namespace ribi {
namespace mb {

struct SeagrassColonisationFunction;

class QtSeagrassColonisationFunctionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtSeagrassColonisationFunctionWidget(QWidget *parent = 0);
  ~QtSeagrassColonisationFunctionWidget();
  std::shared_ptr<SeagrassColonisationFunction> GetFunction() const;
  void SetFunction(const std::shared_ptr<SeagrassColonisationFunction>& f);

signals:
  void signal_parameters_changed() const;

private:
  Ui::QtSeagrassColonisationFunctionWidget *ui;

private slots:
  void OnAnyChange();
};

} //~namespace mb
} //~namespace ribi

#endif // QTSEAGRASSCOLONISATIONFUNCTIONWIDGET_H
