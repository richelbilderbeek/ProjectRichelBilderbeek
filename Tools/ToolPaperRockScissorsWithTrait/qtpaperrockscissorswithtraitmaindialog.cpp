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

#include "qtpaperrockscissorswithtraitwidget.h"
#include "ui_qtpaperrockscissorswithtraitmaindialog.h"

QtPaperRockScissorsWithTraitMainDialog::QtPaperRockScissorsWithTraitMainDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtPaperRockScissorsWithTraitMainDialog),
  m_widget{
    new QtPaperRockScissorsWithTraitWidget(
      600,
      400,
      ribi::prswt::Initialization::random,
      42,
      this
    )
  },
  m_curve_popsizes_paper(new QwtPlotCurve),
  m_curve_popsizes_rock(new QwtPlotCurve),
  m_curve_popsizes_scissors(new QwtPlotCurve),
  m_curve_traits_paper(new QwtPlotCurve),
  m_curve_traits_rock(new QwtPlotCurve),
  m_curve_traits_scissors(new QwtPlotCurve)

{
  ui->setupUi(this);

  using Prs = ribi::PaperRockScissors;
  using QtWidget = QtPaperRockScissorsWithTraitWidget;

  {
    const auto my_layout = ui->widget_grid->layout();
    assert(my_layout);
    my_layout->addWidget(m_widget);
    m_widget->setMinimumSize(100,100);
  }

  ui->plot_popsizes->setTitle("Population sizes in time");
  ui->plot_traits->setTitle("Traits in time");

  ui->plot_popsizes->setCanvasBackground(QColor(255,255,255));

  m_curve_popsizes_paper->attach(ui->plot_popsizes);
  m_curve_popsizes_paper->setStyle(QwtPlotCurve::Lines);
  m_curve_popsizes_paper->setPen(QPen(QtWidget::ToRgb(Prs::paper)));

  m_curve_popsizes_rock->attach(ui->plot_popsizes);
  m_curve_popsizes_rock->setStyle(QwtPlotCurve::Lines);
  m_curve_popsizes_rock->setPen(QPen(QtWidget::ToRgb(Prs::rock)));

  m_curve_popsizes_scissors->attach(ui->plot_popsizes);
  m_curve_popsizes_scissors->setStyle(QwtPlotCurve::Lines);
  m_curve_popsizes_scissors->setPen(QPen(QtWidget::ToRgb(Prs::scissors)));

  ui->plot_traits->setCanvasBackground(QColor(255,255,255));

  m_curve_traits_paper->attach(ui->plot_traits);
  m_curve_traits_paper->setStyle(QwtPlotCurve::Lines);
  m_curve_traits_paper->setPen(QPen(QtWidget::ToRgb(Prs::paper)));

  m_curve_traits_rock->attach(ui->plot_traits);
  m_curve_traits_rock->setStyle(QwtPlotCurve::Lines);
  m_curve_traits_rock->setPen(QPen(QtWidget::ToRgb(Prs::rock)));

  m_curve_traits_scissors->attach(ui->plot_traits);
  m_curve_traits_scissors->setStyle(QwtPlotCurve::Lines);
  m_curve_traits_scissors->setPen(QPen(QtWidget::ToRgb(Prs::scissors)));

  QObject::connect(ui->box_height,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_width,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initialization_type,SIGNAL(currentIndexChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_rng_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(this->m_widget,SIGNAL(signal_next()),this,SLOT(OnNext()));
  OnAnyChange();
}

QtPaperRockScissorsWithTraitMainDialog::~QtPaperRockScissorsWithTraitMainDialog()
{
  delete ui;
}

void QtPaperRockScissorsWithTraitMainDialog::OnAnyChange()
{
  using Init = ribi::prswt::Initialization;
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
  else if (text == "Monomorph")
  {
    init = Init::monomorph;
  }
  else
  {
    std::cerr << text << std::endl;
    assert(!"Should not get here");
  }

  m_timeseries.clear();
  m_popsizes_paper.clear();
  m_popsizes_rock.clear();
  m_popsizes_scissors.clear();
  m_traits_paper.clear();
  m_traits_rock.clear();
  m_traits_scissors.clear();


  m_widget->SetAll(
    ui->box_width->value(),
    ui->box_height->value(),
    init,
    ui->box_rng_seed->value()
  );
}

void QtPaperRockScissorsWithTraitMainDialog::OnNext()
{

  m_timeseries.emplace_back(m_timeseries.empty() ? 0.0 : m_timeseries.back() + 1.0);
  const auto popsizes = m_widget->GetLastPopSizes();
  const auto traits = m_widget->GetLastMeanTraits();

  m_popsizes_paper.emplace_back(std::get<0>(popsizes));
  m_popsizes_rock.emplace_back(std::get<1>(popsizes));
  m_popsizes_scissors.emplace_back(std::get<2>(popsizes));

  m_traits_paper.emplace_back(std::get<0>(traits));
  m_traits_rock.emplace_back(std::get<1>(traits));
  m_traits_scissors.emplace_back(std::get<2>(traits));

  m_curve_popsizes_paper->setData(new QwtPointArrayData(&m_timeseries[0],&m_popsizes_paper[0],m_popsizes_paper.size()));
  m_curve_popsizes_rock->setData(new QwtPointArrayData(&m_timeseries[0],&m_popsizes_rock[0],m_popsizes_rock.size()));
  m_curve_popsizes_scissors->setData(new QwtPointArrayData(&m_timeseries[0],&m_popsizes_scissors[0],m_popsizes_scissors.size()));

  m_curve_traits_paper->setData(new QwtPointArrayData(&m_timeseries[0],&m_traits_paper[0],m_traits_paper.size()));
  m_curve_traits_rock->setData(new QwtPointArrayData(&m_timeseries[0],&m_traits_rock[0],m_traits_rock.size()));
  m_curve_traits_scissors->setData(new QwtPointArrayData(&m_timeseries[0],&m_traits_scissors[0],m_traits_scissors.size()));

  ui->plot_popsizes->replot();
  ui->plot_traits->replot();

}
