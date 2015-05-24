#include "qtlizardpaperrockscissorsspockmaindialog.h"

#include <cassert>
#include <iostream>

#include "lizardpaperrockscissorsspocksimulation.h"
#include "qtlizardpaperrockscissorsspockwidget.h"

#include "ui_qtlizardpaperrockscissorsspockmaindialog.h"

QtLizardPaperRockScissorsSpockMainDialog::QtLizardPaperRockScissorsSpockMainDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtLizardPaperRockScissorsSpockMainDialog),
  m_widget{
    new QtLizardPaperRockScissorsSpockWidget(
      600,
      400,
      //LizardPaperRockScissorsSpockSimulation::Initialization::random,
      ribi::lprss::Simulation::Initialization::random,
      this
    )
  }
{
  ui->setupUi(this);

  {
    const auto my_layout = ui->widget_grid->layout();
    assert(my_layout);
    my_layout->addWidget(m_widget);

  }
  QObject::connect(ui->box_height,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_width,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initialization_type,SIGNAL(currentIndexChanged(int)),this,SLOT(OnAnyChange()));

  OnAnyChange();
}

QtLizardPaperRockScissorsSpockMainDialog::~QtLizardPaperRockScissorsSpockMainDialog()
{
  delete ui;
}

void QtLizardPaperRockScissorsSpockMainDialog::OnAnyChange()
{
  using Init = ribi::lprss::Simulation::Initialization;
  const std::string text{
   ui->box_initialization_type->currentText().toStdString()};
  Init init = Init::random;
  if (text == "Vertical bands")
  {
    init = Init::vertical_bands;
  }
  else if (text == "Random")
  {
    init = Init::random;
  }
  else
  {
    std::cerr << text << std::endl;
    assert(!"Should not get here");
  }

  m_widget->SetAll(
    ui->box_width->value(),
    ui->box_height->value(),
    init
  );
}
