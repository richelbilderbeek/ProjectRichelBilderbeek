#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtkalmanfilterermaindialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QVBoxLayout>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_grid.h"
#include "qwt_legend.h"

#include "kalmanfilterexperiment.h"
#include "kalmanfilterexample.h"
#include "kalmanfilterparameters.h"
#include "kalmanfilter.h"
#include "matrix.h"
#include "qtfixedlagsmootherkalmanfiltercalculationdialog.h"
#include "qtstandardkalmanfiltercalculationdialog.h"
#include "qtsteadystatekalmanfiltercalculationdialog.h"
#include "qtkalmanfilterexamplesdialog.h"
#include "qtkalmanfilterdialog.h"
#include "qtmatrix.h"
#include "qtwhitenoisesystemparametersdialog.h"
#include "trace.h"
#include "ui_qtkalmanfilterermaindialog.h"
#include "standardwhitenoisesystemparameters.h"

QtKalmanFiltererMainDialog::QtKalmanFiltererMainDialog(
  const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtKalmanFiltererMainDialog),
    m_experiment_dialog(new QtKalmanFilterExperimentDialog(model)),
    m_model(model)
{
  #ifndef NDEBUG
  Test();
  #endif


  ui->setupUi(this);
  assert(m_experiment_dialog);
  assert(m_model);
  assert(ui->scroll_area_parameters_layout->layout());


  //ui->scroll_area_parameters_layout->layout()->addWidget(new QLabel("Experiment parameters"));
  ui->scroll_area_parameters_layout->layout()->addWidget(m_experiment_dialog);

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    const QRect window_rect = screen.adjusted(16,32,-16,-64);
    this->setGeometry(window_rect);
    this->move( window_rect.center() - this->rect().center() );
  }
  {
    //Move splitter
    assert(ui->splitter->sizes().size() == 2 && "Splitter manages two areas");
    ui->splitter->setSizes( { 400, this->width() - 400 } );
  }


  assert(this->m_experiment_dialog);

  assert(m_model->CreateExperiment() && "Can get an empty experiment");


  this->m_experiment_dialog->ClickExample(0);

  this->ui->button_start->click();

}

QtKalmanFiltererMainDialog::~QtKalmanFiltererMainDialog()
{
  delete ui;
  delete m_experiment_dialog;
}

boost::shared_ptr<QtKalmanFiltererMainDialog> QtKalmanFiltererMainDialog::Create()
{

  const boost::shared_ptr<QtKalmanFilterExperimentModel> model(
    new QtKalmanFilterExperimentModel);
  assert(model);

  boost::shared_ptr<QtKalmanFiltererMainDialog> d(
    new QtKalmanFiltererMainDialog(model));
  assert(d);

  return d;
}


const std::vector<std::vector<double> > QtKalmanFiltererMainDialog::CreateData(
  const std::vector<boost::numeric::ublas::vector<double> >& a,
  const std::vector<boost::numeric::ublas::vector<double> >& b,
  const std::vector<boost::numeric::ublas::vector<double> >& c,
  const std::vector<boost::numeric::ublas::vector<double> >& d)
{
  //d contains all the inputs of an experiment and always has maximum size
  //assert(a.size() >= 0 && "Always true");
  assert(a.size() == b.size());
  assert(a.size() == c.size());
  assert(a.size() <= d.size() && "Because an experiment might fail, causing a to contain less values");
  //assert(a.size() == 0 || a[0].size() >= 0); //Trivial second term
  assert(a.size() == 0 || a[0].size() == a[0].size());
  assert(a.size() == 0 || a[0].size() == b[0].size());
  assert(a.size() == 0 || a[0].size() == c[0].size());
  assert(a.size() == 0 || a[0].size() == d[0].size());
  const std::size_t time = a.size();

  const std::size_t state_sz = d.empty() ? 0 : d[0].size();

  std::vector<std::vector<double> > v(state_sz * 4,std::vector<double>(time,0.0));

  for (std::size_t t=0; t!=time; ++t)
  {
    assert(t < a.size());
    assert(t < b.size());
    assert(t < c.size());
    assert(t < d.size());
    const boost::numeric::ublas::vector<double>& row_a = a[t];
    const boost::numeric::ublas::vector<double>& row_b = b[t];
    const boost::numeric::ublas::vector<double>& row_c = c[t];
    const boost::numeric::ublas::vector<double>& row_d = d[t];
    assert(state_sz == row_a.size());
    assert(state_sz == row_b.size());
    assert(state_sz == row_c.size());
    assert(state_sz == row_d.size());
    for (std::size_t s=0; s!=state_sz; ++s)
    {
      assert((s*4)+0 < v.size());
      assert((s*4)+1 < v.size());
      assert((s*4)+2 < v.size());
      assert((s*4)+3 < v.size());
      assert(s < row_a.size());
      assert(s < row_b.size());
      assert(s < row_c.size());
      assert(s < row_d.size());
      v[(s*4)+0][t] = row_a[s];
      v[(s*4)+1][t] = row_b[s];
      v[(s*4)+2][t] = row_c[s];
      v[(s*4)+3][t] = row_d[s];
    }
  }
  assert(v.size() == 4 * (d.empty() ? 0 : d[0].size()));
  return v;
}

const boost::shared_ptr<QtKalmanFilterCalculationDialog> QtKalmanFiltererMainDialog::CreateKalmanFilterCalculationDialog(
  const KalmanFilterType type) const
{
  boost::shared_ptr<QtKalmanFilterCalculationDialog> p;
  switch (type)
  {
    case KalmanFilterType::standard:
    {
      p.reset(new QtStandardKalmanFilterCalculationDialog);
    }
    break;
    case KalmanFilterType::steady_state:
    {
      p.reset(new QtSteadyStateKalmanFilterCalculationDialog);
    }
    break;
    case KalmanFilterType::fixed_lag_smoother:
    {
      p.reset(new QtFixedLagSmootherKalmanFilterCalculationDialog);
    }
    break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented KalmanFilterType");
  }
  assert(p);
  assert(p->GetType() == type);
  return p;
}

void QtKalmanFiltererMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtKalmanFiltererMainDialog::on_button_start_clicked()
{
  //Remove previous dialogs
  m_plots.resize(0);
  m_calculations.resize(0);
  delete ui->scroll_area_calculation_contents->layout();
  delete ui->scroll_area_graph_contents->layout();
  assert(!ui->scroll_area_calculation_contents->layout());
  assert(!ui->scroll_area_graph_contents->layout());

  //Do the sim
  assert(m_experiment_dialog);
  const boost::shared_ptr<const KalmanFilterExperiment> experiment = m_model->CreateExperiment();

  assert(experiment);
  assert(experiment->IsValid());
  //Display data as algorithm
  if (ui->box_show_calculation->isChecked())
  {
    ShowCalculationExperiment(experiment);
  }
  //Display data as graph
  if (ui->box_show_graphs->isChecked())
  {
    Plot(experiment);
  }
}

void QtKalmanFiltererMainDialog::Plot(const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(experiment->IsValid());
  assert(m_plots.empty());
  //Make fresh graph section
  assert(!ui->scroll_area_graph_contents->layout());
  ui->scroll_area_graph_contents->setLayout(new QVBoxLayout);
  assert(ui->scroll_area_graph_contents->layout());

  //Create plots
  const int state_size = boost::numeric_cast<int>(experiment->GetStateNames().size());
  std::vector<QwtPlotCurve *> curves;
  for (int i=0; i!=state_size; ++i)
  {
    boost::shared_ptr<QwtPlot> plot(new QwtPlot);
    plot->setTitle(experiment->GetStateNames()[i].c_str());
    plot->setAxisTitle(QwtPlot::xBottom,"Time");
    #ifdef _WIN32
    plot->setCanvasBackground(QBrush(QColor(255,255,255)));
    #else
    plot->setCanvasBackground(QColor(255,255,255));
    #endif

    QwtPlotCurve * const curve_real = new QwtPlotCurve;
    curve_real->setTitle("Real");
    curve_real->attach(plot.get());
    curve_real->setStyle(QwtPlotCurve::Lines);
    curve_real->setPen(QPen(QColor(0,0,255)));

    QwtPlotCurve * const curve_measured = new QwtPlotCurve;
    curve_measured->setTitle("Measured");
    curve_measured->attach(plot.get());
    curve_measured->setStyle(QwtPlotCurve::Lines);
    curve_measured->setPen(QPen(QColor(0,196,0)));

    QwtPlotCurve * const curve_predication = new QwtPlotCurve;
    curve_predication->setTitle("Kalman prediction");
    curve_predication->attach(plot.get());
    curve_predication->setStyle(QwtPlotCurve::Lines);
    curve_predication->setPen(QPen(QColor(255,0,0)));

    QwtPlotCurve * const curve_input = new QwtPlotCurve;
    curve_input->setTitle("Input");
    curve_input->attach(plot.get());
    curve_input->setStyle(QwtPlotCurve::Lines);
    curve_input->setPen(QPen(QColor(0,0,0)));
    curves.push_back(curve_real);
    curves.push_back(curve_measured);
    curves.push_back(curve_predication);
    curves.push_back(curve_input);
    m_plots.push_back(plot);

    //Add grid
    {
      QwtPlotGrid * const grid = new QwtPlotGrid;
      grid->setPen(QPen(QColor(128,128,128)));
      grid->attach(plot.get());
    }
    //Add zoomer
    {
      new QwtPlotZoomer(plot->canvas());
    }
    {
      // legend
      QwtLegend * const legend = new QwtLegend;
      legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
      plot->insertLegend(legend, QwtPlot::RightLegend);
    }
    assert(ui->scroll_area_graph_contents->layout());
    ui->scroll_area_graph_contents->layout()->addWidget(plot.get());
  }
  assert(state_size * 1 == boost::numeric_cast<int>(m_plots.size() ) && "One plot per state element");
  assert(state_size * 4 == boost::numeric_cast<int>(curves.size()) && "Four curves per state element");

  //n_timesteps may differ from n_timesteps_desired, because in the actual experiment
  //the innovation variance may become degenerate
  //! Do not use GetInputs() its size: this size is always set to the maximum
  //  duration of the experiment
  const int n_timesteps = boost::numeric_cast<int>(experiment->GetRealStates().size());

  assert(n_timesteps == boost::numeric_cast<int>(experiment->GetRealStates().size()));
  assert(n_timesteps == boost::numeric_cast<int>(experiment->GetPredictedStates().size()));
  assert(n_timesteps == boost::numeric_cast<int>(experiment->GetMeasuredStates().size()));

  //Create time series
  std::vector<double> time_series(n_timesteps,0.0);
  for (int t=0; t!=n_timesteps; ++t) time_series[t] = static_cast<double>(t);

  //Layout the data for plotting
  const std::vector<std::vector<double> > vs = CreateData(
    experiment->GetRealStates(),
    experiment->GetMeasuredStates(),
    experiment->GetPredictedStates(),
    experiment->GetInputs());
  //assert(!vs.empty()); //vs can be empty

  //Leave if there is no data to plot
  if (vs.empty()) return;

  //Put data on curves
  assert(curves.size() == vs.size());
  const std::size_t n_curves = curves.size();
  for (std::size_t i=0; i!=n_curves; ++i)
  {
    assert(i < vs.size());
    const std::vector<double>& v = vs[i];
    assert(n_timesteps == boost::numeric_cast<int>(v.size()));
    #ifdef _WIN32
    curves[i]->setData(new QwtPointArrayData(&time_series[0],&v[0],time_series.size()));
    #else
    curves[i]->setData(&time_series[0],&v[0],time_series.size());
    #endif
  }

  //Put curves in the plots
  const std::size_t n_plots = m_plots.size();
  for (std::size_t i=0; i!=n_plots; ++i)
  {
    const int n_curves_per_plot = 4;

    //Only plot when there is something to plot
    if (vs[(i*n_curves_per_plot)+0].empty()) break;

    assert(i < m_plots.size());
    assert((i*n_curves_per_plot)+3 < vs.size());
    assert(!vs[(i*n_curves_per_plot)+0].empty());
    assert(!vs[(i*n_curves_per_plot)+1].empty());
    assert(!vs[(i*n_curves_per_plot)+2].empty());
    assert(!vs[(i*n_curves_per_plot)+3].empty());

    m_plots[i]->setAxisScale(QwtPlot::xBottom,0.0,n_timesteps);

    const std::vector<double> min_values
      = {
        *std::min_element(vs[(i*n_curves_per_plot)+0].begin(),vs[(i*n_curves_per_plot)+0].end()),
        *std::min_element(vs[(i*n_curves_per_plot)+1].begin(),vs[(i*n_curves_per_plot)+1].end()),
        *std::min_element(vs[(i*n_curves_per_plot)+2].begin(),vs[(i*n_curves_per_plot)+2].end()),
        *std::min_element(vs[(i*n_curves_per_plot)+3].begin(),vs[(i*n_curves_per_plot)+3].end())
      };
    const double min_value = *std::min_element(min_values.begin(),min_values.end());
    const std::vector<double> max_values
      = {
        *std::max_element(vs[(i*n_curves_per_plot)+0].begin(),vs[(i*n_curves_per_plot)+0].end()),
        *std::max_element(vs[(i*n_curves_per_plot)+1].begin(),vs[(i*n_curves_per_plot)+1].end()),
        *std::max_element(vs[(i*n_curves_per_plot)+2].begin(),vs[(i*n_curves_per_plot)+2].end()),
        *std::max_element(vs[(i*n_curves_per_plot)+3].begin(),vs[(i*n_curves_per_plot)+3].end())
      };
    const double max_value = *std::max_element(max_values.begin(),max_values.end());
    m_plots[i]->setAxisScale(
      QwtPlot::yLeft,
      std::abs(min_value - max_value) < 0.01 ? 0.0 : min_value,
      std::abs(min_value - max_value) < 0.01 ? 1.0 : max_value
    );
    m_plots[i]->replot();
  }
}

void QtKalmanFiltererMainDialog::SetShowCalculations(const bool do_show)
{
  ui->box_show_calculation->setChecked(do_show);
}

void QtKalmanFiltererMainDialog::SetShowGraphs(const bool do_show)
{
  ui->box_show_graphs->setChecked(do_show);
}

void QtKalmanFiltererMainDialog::ShowCalculationExperiment(
  const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(m_calculations.empty());
  //Make fresh calculation section
  assert(!ui->scroll_area_calculation_contents->layout());
  ui->scroll_area_calculation_contents->setLayout(new QVBoxLayout);
  assert(ui->scroll_area_calculation_contents->layout());

  //n_timesteps may differ from n_timesteps_desired, because in the actual simulation
  //the innovation variance may become degenerate
  const int n_timesteps = boost::numeric_cast<int>(experiment->GetCalculationElements().size()); //Number of rows

  for (int i=0; i!=n_timesteps; ++i)
  {

    boost::shared_ptr<QtKalmanFilterCalculationDialog> calculation_dialog
      = CreateKalmanFilterCalculationDialog(experiment->GetKalmanFilter()->GetType());

    assert(calculation_dialog);
    assert(calculation_dialog->GetType() == experiment->GetKalmanFilter()->GetType());
    assert(i < boost::numeric_cast<int>(experiment->GetCalculationElements().size()));
    assert(experiment->GetCalculationElements()[i]->IsComplete());

    std::string style_sheet = calculation_dialog->styleSheet().toStdString()
      + std::string("QDialog { background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 ");
    switch (i % 6)
    {
      case 0: style_sheet+= "#f00, stop: 1 #000); }"; break;
      case 1: style_sheet+= "#ff0, stop: 1 #000); }"; break;
      case 2: style_sheet+= "#0f0, stop: 1 #000); }"; break;
      case 3: style_sheet+= "#0ff, stop: 1 #000); }"; break;
      case 4: style_sheet+= "#f0f, stop: 1 #000); }"; break;
      case 5: style_sheet+= "#fff, stop: 1 #000); }"; break;
    }

    calculation_dialog->setStyleSheet(style_sheet.c_str());
    calculation_dialog->SetTime(i);
    calculation_dialog->ShowCalculation(i,experiment);
    m_calculations.push_back(calculation_dialog);
    assert(ui->scroll_area_calculation_contents->layout());
    ui->scroll_area_calculation_contents->layout()->addWidget(calculation_dialog.get());
  }
}

#ifndef NDEBUG
void QtKalmanFiltererMainDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    TRACE("Starting QtKalmanFiltererMainDialog::Test()")
    //Create self
    {
      const boost::shared_ptr<QtKalmanFiltererMainDialog> d
        = QtKalmanFiltererMainDialog::Create();
      assert(d);
      d->SetShowCalculations(true);
      d->SetShowGraphs(true);
      d->on_button_start_clicked();
    }
    //1) Click on example x and write these to a DokuWiki file
    //2) Click on example y and read the file from x
    {
      const boost::shared_ptr<QtKalmanFiltererMainDialog> d
        = QtKalmanFiltererMainDialog::Create();
      assert(d);
      assert(d->m_experiment_dialog);
      const std::string filename = "TempQtKalmanFiltererMainDialogTest.txt";
      const int n_examples = 10;
      for (int x = 0; x!= n_examples; ++x)
      {
        //1) Click on example x and write these to a DokuWiki file
        {
          d->m_experiment_dialog->ClickExample(x);
          d->m_experiment_dialog->SaveToDokuWiki(filename);
        }
        for (int y = 0; y!= n_examples; ++y)
        {
          //2) Click on example y and read the file from x
          d->m_experiment_dialog->ClickExample(y);
          d->m_experiment_dialog->LoadFromDokuWiki(filename);
        }
      }
      //Delete file
      std::remove(filename.c_str());
    }
    TRACE("Finished QtKalmanFiltererMainDialog::Test()")
  }
}
#endif

void QtKalmanFiltererMainDialog::on_button_save_graph_clicked()
{
  const QString filename
    = QFileDialog::getSaveFileName(
      0,
      "Please select a filename to saev the graphs to",
      QString(),
      "*.png"
    );
  if (filename.isEmpty()) return;

  QImage image(
    ui->scroll_area_graph_contents->contentsRect().size(),
    QImage::Format_ARGB32);    // Create the image with the exact size
  image.fill(Qt::transparent); // Start all pixels transparent
  QPainter painter(&image);
  ui->scroll_area_graph_contents->render(&painter);

  image.save(filename);
  assert(QFile::exists(filename));
}
