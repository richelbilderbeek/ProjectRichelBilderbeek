#include "qttesthistogrammaindialog.h"

#include <fstream>
#include <QDesktopWidget>
#include <QFileDialog>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_barchart.h>
#include <qwt_plot_curve.h>

#include "histogram.h"
#include "ui_qttesthistogrammaindialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtTestHistogramMainDialog::QtTestHistogramMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestHistogramMainDialog),
  m_curve_histogram(new QwtPlotCurve)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->plot_histogram->setTitle("Histogram");

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(ui->plot_histogram);
  }
  //Add zoomer
  {
    new QwtPlotZoomer(ui->plot_histogram->canvas());
  }

  ui->plot_histogram->setCanvasBackground(QColor(255,255,255));

  m_curve_histogram->attach(ui->plot_histogram);
  m_curve_histogram->setStyle(QwtPlotCurve::Lines);
  m_curve_histogram->setPen(QPen(QColor(0,0,0)));

  QObject::connect(ui->box_n,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->box_mean,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_stddev,SIGNAL(valueChanged(double)),this,SLOT(Run()));

  Run();

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestHistogramMainDialog::~QtTestHistogramMainDialog()
{
  delete ui;
}

void QtTestHistogramMainDialog::Run()
{
  static std::mt19937 mt(42);
  std::normal_distribution<double> d(
    ui->box_mean->value(),
    ui->box_stddev->value()
  );

  const int n{ui->box_n->value()};
  std::vector<double> v;
  for (int i=0; i!=n; ++i)
  {
    const double x{d(mt)};
    v.push_back(x);
  }
  Histogram histogram(
    v,
    *std::min_element(std::begin(v),std::end(v)) - 1.0,
    *std::max_element(std::begin(v),std::end(v)) + 1.0,
    1 + std::sqrt(n)
  );

  std::vector<double> xs;
  std::vector<double> ys;
  for (const auto& h: histogram.GetHistogram())
  {
    xs.push_back(h.GetMid());
    ys.push_back(static_cast<double>(h.GetCnt()));
  }

  m_curve_histogram->setData(new QwtPointArrayData(&xs[0],&ys[0],ys.size()));
  ui->plot_histogram->replot();

}
