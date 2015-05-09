#ifndef QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
#define QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H

#include <QWidget>

namespace Ui {
class QtMutualismBreakdownerParametersWidget;
}

class QtMutualismBreakdownerParametersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerParametersWidget(QWidget *parent = 0);
  ~QtMutualismBreakdownerParametersWidget();

private:
  Ui::QtMutualismBreakdownerParametersWidget *ui;
};

#endif // QTMUTUALISMBREAKDOWNERPARAMETERSWIDGET_H
