/*
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include <cassert>
#include <fstream>
#include <QDesktopWidget>
#include <QGridLayout>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "timesimulation.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#include "ui_qtmutualismbreakdownerequilibriumdialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtMutualismBreakdownerEquilibriumDialog::QtMutualismBreakdownerEquilibriumDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerEquilibriumDialog),
  m_curve_equilbrium_from_low(new QwtPlotCurve),
  m_curve_equilbrium_from_high(new QwtPlotCurve),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  assert(this->ui->widget->layout());
  this->ui->widget->layout()->addWidget(m_parameters_widget);

  ui->plot_equilibrium->setTitle("Equilibrium");

  //Add grid
  for (const auto plot:
    {
      ui->plot_equilibrium,
    }
  )
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(196,196,196)));
    grid->attach(plot);
    new QwtPlotZoomer(plot->canvas());
  }

  ui->plot_equilibrium->setCanvasBackground(QColor(255,255,255));

  m_curve_equilbrium_from_low->attach(ui->plot_equilibrium);
  m_curve_equilbrium_from_low->setStyle(QwtPlotCurve::Lines);
  m_curve_equilbrium_from_low->setPen(QColor(255,0,0));
  m_curve_equilbrium_from_high->attach(ui->plot_equilibrium);
  m_curve_equilbrium_from_high->setStyle(QwtPlotCurve::Lines);
  m_curve_equilbrium_from_high->setPen(QColor(0,0,255));

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(on_button_run_clicked()));
  on_button_run_clicked();

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtMutualismBreakdownerEquilibriumDialog::~QtMutualismBreakdownerEquilibriumDialog()
{
  delete ui;
}


Parameters QtMutualismBreakdownerEquilibriumDialog::GetParameters() const noexcept
{
  return this->m_parameters_widget->GetParameters();
}

void QtMutualismBreakdownerEquilibriumDialog::SetParameters(const Parameters& parameters) noexcept
{
  this->m_parameters_widget->SetParameters(parameters);
}



void QtMutualismBreakdownerEquilibriumDialog::on_button_run_clicked()
{
  Parameters parameters{GetParameters()};

  std::vector<double> thetas; //desiccation stresses
  std::vector<double> ns_from_low; //seagrass equilibrium densities
  std::vector<double> ns_from_high; //seagrass equilibrium densities

  for (double theta=0.0; theta<=10.0; theta+=1.0)
  {
    thetas.push_back(theta);
    //From low
    {
      parameters.SetInitialSeagrassDensity(0.1 * boost::units::si::species_per_square_meter);
      TimeSimulation simulation(parameters);
      simulation.Run();
      if (simulation.GetSeagrassDensities().empty())
      {
        ns_from_low.push_back(0.0);
      }
      else
      {
        const auto n_end = simulation.GetSeagrassDensities().back();
        ns_from_low.push_back(n_end.value());
      }
    }
    //From high
    {
      parameters.SetInitialSeagrassDensity(1.0 * boost::units::si::species_per_square_meter);
      TimeSimulation simulation(parameters);
      simulation.Run();
      if (simulation.GetSeagrassDensities().empty())
      {
        ns_from_high.push_back(0.0);
      }
      else
      {
        const auto n_end = simulation.GetSeagrassDensities().back();
        ns_from_high.push_back(n_end.value());
      }
    }
  }

  m_curve_equilbrium_from_low->setData(
    new QwtPointArrayData(&thetas[0],&ns_from_low[0],ns_from_low.size())
  );
  m_curve_equilbrium_from_high->setData(
    new QwtPointArrayData(&thetas[0],&ns_from_high[0],ns_from_high.size())
  );
  ui->plot_equilibrium->replot();

}
*/
