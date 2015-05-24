#include "qtpaperrockscissorsmaindialog.h"

#include <cassert>
#include <iostream>

#include "qtpaperrockscissorswidget.h"
#include "ui_qtpaperrockscissorsmaindialog.h"

QtPaperRockScissorsMainDialog::QtPaperRockScissorsMainDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtPaperRockScissorsMainDialog),
  m_widget{
    new QtPaperRockScissorsWidget(
      600,
      400,
      ribi::prs::PaperRockScissorsSimulation::Initialization::random,
      42,
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
  QObject::connect(ui->box_rng_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));

  OnAnyChange();
}

QtPaperRockScissorsMainDialog::~QtPaperRockScissorsMainDialog()
{
  delete ui;
}

void QtPaperRockScissorsMainDialog::OnAnyChange()
{
  using Init = ribi::prs::PaperRockScissorsSimulation::Initialization;
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
    init,
    ui->box_rng_seed->value()
  );
}
