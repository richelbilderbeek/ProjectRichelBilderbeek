#ifndef QTBIRTHDEATHMODELPARAMETERSWIDGET_H
#define QTBIRTHDEATHMODELPARAMETERSWIDGET_H

#include <QWidget>
#include "birthdeathmodelparameters.h"

namespace Ui {
class QtBirthDeathModelParametersWidget;
}

class QtBirthDeathModelParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBirthDeathModelParametersWidget(QWidget *parent = 0);
  QtBirthDeathModelParametersWidget(const QtBirthDeathModelParametersWidget&) = delete;
  QtBirthDeathModelParametersWidget& operator=(const QtBirthDeathModelParametersWidget&) = delete;
  ~QtBirthDeathModelParametersWidget();

  ribi::bdm::Parameters GetParameters() const noexcept;

signals:
  void signal_parameters_changed();

private:
  Ui::QtBirthDeathModelParametersWidget *ui;

private slots:
  void OnAnyChange() noexcept;
};

#endif // QTBIRTHDEATHMODELPARAMETERSWIDGET_H
