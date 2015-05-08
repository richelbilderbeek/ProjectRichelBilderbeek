#include "qtsumbrownianmotionsmaindialog.h"

#include <fstream>
#include <QDesktopWidget>
#include <QFileDialog>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_barchart.h>
#include <qwt_plot_curve.h>

#include "simulation.h"
#include "ui_qtsumbrownianmotionsmaindialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtSumBrownianMotionsMainDialog::QtSumBrownianMotionsMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtSumBrownianMotionsMainDialog),
  m_curve_a(new QwtPlotCurve),
  m_curve_b(new QwtPlotCurve),
  m_curve_sum(new QwtPlotCurve)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  ui->plot_a->setTitle("A");
  ui->plot_b->setTitle("B");
  ui->plot_sum->setTitle("Sum");

  //Add grid
  for (const auto plot:
    {
      ui->plot_a,
      ui->plot_b,
      ui->plot_sum
    }
  )
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(plot);
    new QwtPlotZoomer(plot->canvas());
  }

  ui->plot_a->setCanvasBackground(QColor(226,226,255));
  ui->plot_b->setCanvasBackground(QColor(226,255,226));
  ui->plot_sum->setCanvasBackground(QColor(255,226,226));

  m_curve_a->attach(ui->plot_a);
  m_curve_a->setStyle(QwtPlotCurve::Lines);
  m_curve_a->setPen(QPen(QColor(0,0,255)));

  m_curve_b->attach(ui->plot_b);
  m_curve_b->setStyle(QwtPlotCurve::Lines);
  m_curve_b->setPen(QPen(QColor(0,255,0)));

  m_curve_sum->attach(ui->plot_sum);
  m_curve_sum->setStyle(QwtPlotCurve::Lines);
  m_curve_sum->setPen(QPen(QColor(255,0,0)));

  QObject::connect(ui->box_n,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->box_mean_a,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_stddev_a,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_mean_b  ,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_stddev_b,SIGNAL(valueChanged(double)),this,SLOT(Run()));

  Run();

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtSumBrownianMotionsMainDialog::~QtSumBrownianMotionsMainDialog()
{
  delete ui;
}


Parameters QtSumBrownianMotionsMainDialog::GetParameters() const noexcept
{
  Parameters p(
    ui->box_n->value(),
    ui->box_mean_a->value(),
    ui->box_stddev_a->value(),
    ui->box_mean_b->value(),
    ui->box_stddev_b->value()
  );

  return p;
}

void QtSumBrownianMotionsMainDialog::SetParameters(const Parameters& parameters) noexcept
{
  ui->box_mean_a->setValue(parameters.mean_a);
  ui->box_stddev_a->setValue(parameters.stddev_a);
  ui->box_mean_b->setValue(parameters.mean_b);
  ui->box_stddev_b->setValue(parameters.stddev_b);
  ui->box_n->setValue(parameters.n);
}

void QtSumBrownianMotionsMainDialog::Run()
{
  Simulation simulation(GetParameters());
  simulation.Run();

  const std::vector<double>& axs{simulation.GetAxs()};
  const std::vector<double>& ays{simulation.GetAys()};
  const std::vector<double>& bxs{simulation.GetBxs()};
  const std::vector<double>& bys{simulation.GetBys()};
  const std::vector<double>& sumxs{simulation.GetSumxs()};
  const std::vector<double>& sumys{simulation.GetSumys()};

  m_curve_a->setData(new QwtPointArrayData(&axs[0],&ays[0],ays.size()));
  m_curve_b->setData(new QwtPointArrayData(&bxs[0],&bys[0],bys.size()));
  m_curve_sum->setData(new QwtPointArrayData(&sumxs[0],&sumys[0],sumys.size()));


  ui->plot_a->replot();
  ui->plot_b->replot();
  ui->plot_sum->replot();
}
