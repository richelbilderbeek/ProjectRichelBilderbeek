#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttextpositionwidget.h"
#include "qttesttextpositionwidgetmaindialog.h"
#include "ui_qttesttextpositionwidgetmaindialog.h"
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
