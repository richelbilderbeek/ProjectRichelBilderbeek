#include "qtmutualismbreakdownertestpoisoningfunctiondialog.h"

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

#include "poisoningfunction.h"
#include "ui_qtmutualismbreakdownertestpoisoningfunctiondialog.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtMutualismBreakdownerTestPoisoningFunctionDialog::QtMutualismBreakdownerTestPoisoningFunctionDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerTestPoisoningFunctionDialog),
  m_curve(new QwtPlotCurve),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  assert(this->ui->widget->layout());
  this->ui->widget->layout()->addWidget(m_parameters_widget);

  ui->plot->setTitle("Poisoning");

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

  ui->plot->setCanvasBackground(QColor(255,255,255));

  m_curve->attach(ui->plot);
  m_curve->setStyle(QwtPlotCurve::Lines);
  m_curve->setPen(QPen(QColor(0,0,0)));


 Run();

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(Run()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtMutualismBreakdownerTestPoisoningFunctionDialog::~QtMutualismBreakdownerTestPoisoningFunctionDialog()
{
  delete ui;
}


Parameters QtMutualismBreakdownerTestPoisoningFunctionDialog::GetParameters() const noexcept
{
  assert(m_parameters_widget);
  return m_parameters_widget->GetParameters();
}

void QtMutualismBreakdownerTestPoisoningFunctionDialog::SetParameters(const Parameters& parameters) noexcept
{
  assert(m_parameters_widget);
  m_parameters_widget->SetParameters(parameters);
}


void QtMutualismBreakdownerTestPoisoningFunctionDialog::Run()
{
  const auto f
    = m_parameters_widget->GetParameters().GetPoisoningFunction()
  ;
  assert(f);
  assert(f.get());
  std::vector<double> sulfide_concentrations;
  std::vector<double> survivals;

  for (double s = 0.0; s != 100.0; s += 1.0)
  {
    sulfide_concentrations.push_back(s);
    const auto sulfilde_concentration
      = s * boost::units::si::mole / boost::units::si::cubic_meter;
    const double poisoning{ f->CalculateSurvivalFraction(sulfilde_concentration)};
    survivals.push_back(poisoning);
  }

  m_curve->setData(
    new QwtPointArrayData(&sulfide_concentrations[0],&survivals[0],survivals.size())
  );
  ui->plot->replot();
}
