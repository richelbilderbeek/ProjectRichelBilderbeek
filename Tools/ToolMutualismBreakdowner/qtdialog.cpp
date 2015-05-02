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
  m_curve_seagrass_density(new QwtPlotCurve),
  m_curve_sulfide_concentration(new QwtPlotCurve),
  m_curve_oxygen_concentration(new QwtPlotCurve)
{
  ui->setupUi(this);

  ui->plot_seagrass_density->setTitle("Seagrass density");
  ui->plot_sulfide_concentration->setTitle("Sulfide concentration");
  ui->plot_oxygen_concentration->setTitle("Oxygen concentration");

  ui->plot_seagrass_density->setCanvasBackground(QColor(226,255,226));
  ui->plot_sulfide_concentration->setCanvasBackground(QColor(255,226,226));
  ui->plot_oxygen_concentration->setCanvasBackground(QColor(226,226,255));

  m_curve_seagrass_density->attach(ui->plot_seagrass_density);
  m_curve_seagrass_density->setStyle(QwtPlotCurve::Lines);
  m_curve_seagrass_density->setPen(QPen(QColor(0,255,0)));


  m_curve_sulfide_concentration->attach(ui->plot_sulfide_concentration);
  m_curve_sulfide_concentration->setStyle(QwtPlotCurve::Lines);
  m_curve_sulfide_concentration->setPen(QPen(QColor(255,0,0)));

  m_curve_oxygen_concentration->attach(ui->plot_oxygen_concentration);
  m_curve_oxygen_concentration->setStyle(QwtPlotCurve::Lines);
  m_curve_oxygen_concentration->setPen(QPen(QColor(0,0,255)));

  QObject::connect(
    ui->box_n_timesteps,
    SIGNAL(valueChanged(int)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_initial_seagrass_density,
    SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_seagrass_growth_rate,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_seagrass_senescense,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_sulfide_mol_per_seagrass_density,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_sulfide_toxicity,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_oxygen_inhibition_strength,SIGNAL(valueChanged(double)),
    this,SLOT(Run())
  );
  QObject::connect(
    ui->box_oxygen_production,SIGNAL(valueChanged(double)),
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
  const int n_timesteps{
    ui->box_n_timesteps->value()
  };
  std::vector<double> seagrass_densities;
  std::vector<double> sulfide_concentrations;
  std::vector<double> oxygen_concentrations;
  std::vector<double> timeseries;
  const double initial_seagrass_density{
    ui->box_initial_seagrass_density->value()
  };

  const double seagrass_carrying_capacity{1.0};
  const double seagrass_growth_rate{
    ui->box_seagrass_growth_rate->value()
  };
  const double seagrass_senescence{
    ui->box_seagrass_senescense->value()
  };
  const double sulfide_mol_per_seagrass_density{
    ui->box_sulfide_mol_per_seagrass_density->value()
  };

  const double sulfide_toxicity{
    ui->box_sulfide_toxicity->value()
  };

  const double oxygen_inhibition_strength{
    ui->box_oxygen_inhibition_strength->value()
  };
  const double oxygen_production{
    ui->box_oxygen_production->value()
  };


  //Initialize sim
  double seagrass_density{initial_seagrass_density};
  double sulfide_concentration{0.0};
  //double oxygen_concentration{initial_oxygen_concentration};
  for (int i=0; i!=n_timesteps; ++i)
  {
    timeseries.push_back(static_cast<double>(i));
    //Sim here
    {
      const double r{seagrass_growth_rate};
      const double k{seagrass_carrying_capacity};
      const double n{seagrass_density};
      const double m{seagrass_senescence};
      const double t{sulfide_toxicity};
      const double s{sulfide_concentration};
      seagrass_density
        += r*n*(1.0-(n/k)) //Growth
        - (n*m) //Leaf loss
        - (t*s)
      ;
    }
    {
      using std::exp;
      const double n{seagrass_density};
      const double m{seagrass_senescence};
      const double f{sulfide_mol_per_seagrass_density};
      const double a{oxygen_inhibition_strength};
      const double p{oxygen_production};
      sulfide_concentration
        += (n*m*f*exp(-a*p*n))
      ;

    }
    seagrass_densities.push_back(seagrass_density);
    sulfide_concentrations.push_back(sulfide_concentration);
  }
  m_curve_seagrass_density->setData(
    new QwtPointArrayData(&timeseries[0],&seagrass_densities[0],seagrass_densities.size())
  );
  m_curve_sulfide_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&sulfide_concentrations[0],sulfide_concentrations.size())
  );
  m_curve_oxygen_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&oxygen_concentrations[0],oxygen_concentrations.size())
  );
  ui->plot_seagrass_density->replot();
  ui->plot_sulfide_concentration->replot();
  ui->plot_oxygen_concentration->replot();
}
