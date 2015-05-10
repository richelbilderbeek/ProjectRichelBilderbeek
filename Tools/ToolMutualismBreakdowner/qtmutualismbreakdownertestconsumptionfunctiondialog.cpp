#include "qtmutualismbreakdownertestconsumptionfunctiondialog.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QGridLayout>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "loripesconsumptionfunction.h"
#include "ui_qtmutualismbreakdownertestconsumptionfunctiondialog.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtMutualismBreakdownerTestConsumptionFunctionDialog::QtMutualismBreakdownerTestConsumptionFunctionDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerTestConsumptionFunctionDialog),
  m_curve(new QwtPlotCurve),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  assert(this->ui->widget->layout());
  this->ui->widget->layout()->addWidget(m_parameters_widget);

  ui->plot->setTitle("Loripes sulfide consumption");

  //Add grid
  for (const auto plot:
    {
      ui->plot,
    }
  )
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(plot);
    new QwtPlotZoomer(plot->canvas());
  }

  ui->plot->setCanvasBackground(QColor(226,255,226));

  m_curve->attach(ui->plot);
  m_curve->setStyle(QwtPlotCurve::Lines);
  m_curve->setPen(QPen(QColor(0,255,0)));


 Run();

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(Run()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtMutualismBreakdownerTestConsumptionFunctionDialog::~QtMutualismBreakdownerTestConsumptionFunctionDialog()
{
  delete ui;
}


Parameters QtMutualismBreakdownerTestConsumptionFunctionDialog::GetParameters() const noexcept
{
  assert(m_parameters_widget);
  return m_parameters_widget->GetParameters();
}

void QtMutualismBreakdownerTestConsumptionFunctionDialog::SetParameters(const Parameters& parameters) noexcept
{
  assert(m_parameters_widget);
  m_parameters_widget->SetParameters(parameters);
}


void QtMutualismBreakdownerTestConsumptionFunctionDialog::Run()
{
  std::clog << ".";

  const auto f
    = m_parameters_widget->GetParameters().loripes_consumption_function;
  assert(f);
  assert(f.get());
  std::vector<double> seagrass_densities;
  std::vector<double> consumptions;

  for (double n = 0.0; n != 100.0; n += 1.0)
  {
    seagrass_densities.push_back(n);
    const auto seagrass_density
      = n * boost::units::si::species_per_square_meter;
    const double consumption{ f->CalculateConsumptionRate(seagrass_density)};
    consumptions.push_back(consumption);
  }

  m_curve->setData(
    new QwtPointArrayData(&seagrass_densities[0],&consumptions[0],consumptions.size())
  );
  ui->plot->replot();
}
