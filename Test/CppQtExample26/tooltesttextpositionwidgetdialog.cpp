#include "qttextpositionwidget.h"
#include "tooltesttextpositionwidgetdialog.h"
#include "ui_tooltesttextpositionwidgetdialog.h"

ToolTestTextPositionWidgetDialog::ToolTestTextPositionWidgetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTestTextPositionWidgetDialog)
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

ToolTestTextPositionWidgetDialog::~ToolTestTextPositionWidgetDialog()
{
  delete ui;
}
