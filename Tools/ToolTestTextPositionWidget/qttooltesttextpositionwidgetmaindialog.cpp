#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttextpositionwidget.h"
#include "qttooltesttextpositionwidgetmaindialog.h"
#include "ui_qttooltesttextpositionwidgetmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTextPositionWidgetMainDialog::QtTestTextPositionWidgetMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTextPositionWidgetMainDialog)
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

ribi::QtTestTextPositionWidgetMainDialog::~QtTestTextPositionWidgetMainDialog() noexcept
{
  delete ui;
}
