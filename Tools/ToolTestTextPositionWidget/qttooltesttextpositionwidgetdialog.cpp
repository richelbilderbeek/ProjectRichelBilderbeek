#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttextpositionwidget.h"
#include "qttooltesttextpositionwidgetdialog.h"
#include "ui_qttooltesttextpositionwidgetdialog.h"
#pragma GCC diagnostic pop

QtToolTestTextPositionWidgetDialog::QtToolTestTextPositionWidgetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtToolTestTextPositionWidgetDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(
    new QtTextPositionWidget(
      {
       "Alpha",
       "Beta",
       "Gamma",
       "Delta",
       "Epsilon",
       "Eta"
      }
    )
  );
}

QtToolTestTextPositionWidgetDialog::~QtToolTestTextPositionWidgetDialog() noexcept
{
  delete ui;
}
