#include "qttextpositionwidget.h"
#include "tooltesttextpositionwidgetdialog.h"
#include "ui_tooltesttextpositionwidgetdialog.h"

ToolTestTextPositionWidgetDialog::ToolTestTextPositionWidgetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTestTextPositionWidgetDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtTextPositionWidget( { "A", "B", "C", "D", "E", "F" } ));
}

ToolTestTextPositionWidgetDialog::~ToolTestTextPositionWidgetDialog()
{
  delete ui;
}
