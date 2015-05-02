#include "qtdialog.h"

#include "qwt_plot.h"
#include "qwt_plot_curve.h"

#include "alphabetafilter.h"
#include "ui_qtdialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_curve_seagrass_density(new QwtPlotCurve("Inputs")),
  m_curve_sulfide_concentration(new QwtPlotCurve("Outputs"))
{
  ui->setupUi(this);
  ui->plot_seagrass_density->setCanvasBackground(QColor(226,255,226));
  ui->plot_sulfide_concentration->setCanvasBackground(QColor(255,226,226));

  m_curve_seagrass_density->attach(ui->plot_seagrass_density);
  m_curve_seagrass_density->setStyle(QwtPlotCurve::Lines);
  m_curve_seagrass_density->setPen(QPen(QColor(0,255,0)));

  m_curve_sulfide_concentration->attach(ui->plot_sulfide_concentration);
  m_curve_sulfide_concentration->setStyle(QwtPlotCurve::Lines);
  m_curve_sulfide_concentration->setPen(QPen(QColor(255,0,0)));

  QObject::connect(
    ui->box_initial_seagrass_density,
    SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_initial_sulfide_concentration,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_seagrass_growth_rate,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  Run();
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::Run()
{
  const int timesteps{100};
  std::vector<double> seagrass_densities;
  std::vector<double> sulfide_concentrations;
  std::vector<double> timeseries;
  const double initial_seagrass_density{
    ui->box_initial_seagrass_density->value()
  };
  const double initial_sulfide_concentration{
    ui->box_initial_sulfide_concentration->value()
  };

  const double seagrass_carrying_capacity{1.0};
  const double seagrass_growth_rate{
    ui->box_seagrass_growth_rate->value()
  };

  //Initialize sim
  double seagrass_density{initial_seagrass_density};
  double sulfide_concentration{initial_sulfide_concentration};
  for (int i=0; i!=timesteps; ++i)
  {
    timeseries.push_back(static_cast<double>(i));
    //Sim here
    {
      const double r{seagrass_growth_rate};
      const double k{seagrass_carrying_capacity};
      const double n{seagrass_density};
      seagrass_density += r*n*(1.0-(n/k));
    }

    sulfide_concentration += std::sin(static_cast<double>(i));

    seagrass_densities.push_back(seagrass_density);
    sulfide_concentrations.push_back(sulfide_concentration);
  }
  m_curve_seagrass_density->setData(
    new QwtPointArrayData(&timeseries[0],&seagrass_densities[0],seagrass_densities.size())
  );
  m_curve_sulfide_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&sulfide_concentrations[0],sulfide_concentrations.size())
  );
  ui->plot_seagrass_density->replot();
  ui->plot_sulfide_concentration->replot();
}
