#include "qtpaperrockscissorswithtraitmaindialog.h"

#include <cassert>
#include <iostream>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#if QWT_VERSION >= 0x060100 || !WIN32
#include <qwt_point_data.h>
#endif

#include "qtpaperrockscissorswidget.h"
#include "ui_qtpaperrockscissorswithtraitmaindialog.h"

QtPaperRockScissorsMainDialog::QtPaperRockScissorsMainDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtPaperRockScissorsMainDialog),
  m_widget{
    new QtPaperRockScissorsWidget(
      600,
      400,
      PaperRockScissorsSimulation::Initialization::random,
      42,
      this
    )
  },
  m_curve_popsizes(new QwtPlotCurve),
  m_curve_traits(new QwtPlotCurve)

{
  ui->setupUi(this);

  {
    const auto my_layout = ui->widget_grid->layout();
    assert(my_layout);
    my_layout->addWidget(m_widget);

  }

  ui->plot_popsizes->setTitle("Population sizes in time");
  ui->plot_traits->setTitle("Traits in time");

  ui->plot_popsizes->setCanvasBackground(QColor(255,255,255));
  m_curve_popsizes->attach(ui->plot_popsizes);
  m_curve_popsizes->setStyle(QwtPlotCurve::Lines);
  m_curve_popsizes->setPen(QPen(QColor(0,0,0)));

  ui->plot_traits->setCanvasBackground(QColor(255,255,255));
  m_curve_traits->attach(ui->plot_traits);
  m_curve_traits->setStyle(QwtPlotCurve::Lines);
  m_curve_traits->setPen(QPen(QColor(0,0,0)));

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
  using Init = PaperRockScissorsSimulation::Initialization;
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
