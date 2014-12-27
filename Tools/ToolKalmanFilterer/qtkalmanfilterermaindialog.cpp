#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkalmanfilterermaindialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/signals2.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QVBoxLayout>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
//#include <qwt_plot_seriesitem.h>
#include <qwt_legend.h>

#if QWT_VERSION >= 0x060100
#include <qwt_point_data.h>
#endif

#include "kalmanfilter.h"
#include "kalmanfilterexample.h"
#include "testtimer.h"
#include "kalmanfilterexperiment.h"
#include "kalmanfilterexperimentparametertype.h"
#include "kalmanfilterparameters.h"
#include "matrix.h"
#include "qtcopyalltablewidget.h"
#include "qtfixedlagsmootherkalmanfiltercalculationdialog.h"
#include "qtkalmanfilterdialog.h"
#include "qtkalmanfilterexamplesdialog.h"
#include "qtkalmanfilterexperimentmodel.h"
#include "qtkalmanfilterexperimentdialog.h"
#include "qtmatrix.h"
#include "qtstandardkalmanfiltercalculationdialog.h"
#include "qtsteadystatekalmanfiltercalculationdialog.h"
#include "qtwhitenoisesystemparametersdialog.h"
#include "standardwhitenoisesystemparameters.h"
#include "trace.h"
#include "ui_qtkalmanfilterermaindialog.h"

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
//Due to Qmake error
//http://richelbilderbeek.nl/CppQmakeErrorUnknownModulesInQtLocationSensors.htm
#define DISABLE_QWEBVIEW
#endif

#pragma GCC diagnostic pop

ribi::kalman::QtKalmanFiltererMainDialog::QtKalmanFiltererMainDialog(
  const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtKalmanFiltererMainDialog),
    m_experiment_dialog(new QtKalmanFilterExperimentDialog(model)),
    m_model(model),
    m_plots{},
    m_to_delete_at_new_run{}
{
  #ifndef NDEBUG
  Test();
  #endif


  ui->setupUi(this);
  assert(m_experiment_dialog);
  assert(m_model);
  assert(ui->scroll_area_parameters_layout->layout());
  //TRACE(QWebSettings::globalSettings()->fontFamily(QWebSettings::FixedFont).toStdString());
  #ifndef DISABLE_QWEBVIEW
  QWebSettings::globalSettings()->setFontFamily(QWebSettings::FixedFont,"Courier New");
  QWebSettings::globalSettings()->setFontSize(QWebSettings::DefaultFontSize,14);
  QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,false);
  ui->web_view_context->settings()->setFontFamily(QWebSettings::FixedFont,"Courier New");
  ui->web_view_context->settings()->setFontSize(QWebSettings::DefaultFontSize,14);
  ui->web_view_context->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,false);
  ui->web_view_context->setStyleSheet(
    "QWebView,QWidget,QLabel { "
    "  font-size: 18px;"
    "  font-family: \"Courier New\", \"Courier\", Courier, monospace;"
    "} ");
  #endif

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

  m_model->m_signal_context_changed.connect(
    boost::bind(&ribi::kalman::QtKalmanFiltererMainDialog::OnNewContext,this,boost::lambda::_1));

  ui->box_show_calculation->setChecked(false);
  ui->box_show_statistics->setChecked(true);
  ui->box_show_table->setChecked(false);

  this->GetExperimentDialog()->GetExamplesDialog()->EmitExample(0); //Click the 'Voltage' example
  ui->tab_main->setCurrentIndex(2); //Set to 'Graphs' tab
  this->ui->button_start->click(); //Start the simulation
}

ribi::kalman::QtKalmanFiltererMainDialog::~QtKalmanFiltererMainDialog() noexcept
{
  delete ui;
  delete m_experiment_dialog;
}

boost::shared_ptr<ribi::kalman::QtKalmanFiltererMainDialog> ribi::kalman::QtKalmanFiltererMainDialog::Create()
{

  const boost::shared_ptr<QtKalmanFilterExperimentModel> model{
    new QtKalmanFilterExperimentModel
  };
  assert(model);

  boost::shared_ptr<QtKalmanFiltererMainDialog> d{
    new QtKalmanFiltererMainDialog(model)
  };
  assert(d);

  return d;
}


const std::vector<std::vector<double> > ribi::kalman::QtKalmanFiltererMainDialog::CreateData(
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

const boost::shared_ptr<ribi::kalman::QtKalmanFilterCalculationDialog> ribi::kalman::QtKalmanFiltererMainDialog::CreateKalmanFilterCalculationDialog(
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

const std::vector<double> ribi::kalman::QtKalmanFiltererMainDialog::ExtractAverageSquaredError(
  const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  const std::vector<boost::numeric::ublas::vector<double> > predictions = experiment->GetPredictedStates();
  const std::vector<boost::numeric::ublas::vector<double> > real_states = experiment->GetRealStates();
  assert(real_states.size() == predictions.size());
  const std::size_t n_timesteps = real_states.size();
  if (n_timesteps == 0) return std::vector<double>();
  assert(real_states[0].size() == predictions[0].size());
  const std::size_t n_states = real_states[0].size();
  if (n_states == 0) return std::vector<double>();
  std::vector<double> sum(n_states,0.0);
  //Sum all squared errors
  for (std::size_t timestep=0; timestep!=n_timesteps; ++timestep)
  {
    assert(timestep < predictions.size());
    assert(timestep < real_states.size());
    const boost::numeric::ublas::vector<double>& prediction = predictions[timestep];
    const boost::numeric::ublas::vector<double>& real = real_states[timestep];
    for (std::size_t state=0; state!=n_states; ++state)
    {
      assert(state < prediction.size());
      assert(state < real.size());
      assert(state < sum.size());
      const double p = prediction[state];
      const double r = real[state];
      sum[state] += ((p-r)*(p-r));
    }
  }
  //Obtain the average squared error
  for (std::size_t state=0; state!=n_states; ++state)
  {
    assert(state < sum.size());
    sum[state] /= static_cast<double>(n_timesteps);
  }

  return sum;
}

void ribi::kalman::QtKalmanFiltererMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::kalman::QtKalmanFiltererMainDialog::on_button_save_graph_clicked()
{
  const QString filename
    = QFileDialog::getSaveFileName(
      0,
      "Please select a filename to save the graphs to",
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

void ribi::kalman::QtKalmanFiltererMainDialog::on_button_start_clicked()
{

  assert(this->m_model->CreateWhiteNoiseSystemParameters()->GetType()
    == GetExperimentDialog()->GetNoiseParametersDialog()->GetWhiteNoiseSystemType());


  //Remove previous dialogs
  m_plots.resize(0);
  m_to_delete_at_new_run.resize(0);
  delete ui->scroll_area_calculation_contents->layout();
  delete ui->scroll_area_graph_contents->layout();
  delete ui->scroll_area_statistics_contents->layout();
  delete ui->scroll_area_table_contents->layout();
  assert(!ui->scroll_area_calculation_contents->layout());
  assert(!ui->scroll_area_graph_contents->layout());
  assert(!ui->scroll_area_statistics_contents->layout());
  assert(!ui->scroll_area_table_contents->layout());

  //Do the sim
  assert(m_experiment_dialog);
  const boost::shared_ptr<const KalmanFilterExperiment> experiment = m_model->CreateExperiment();

  assert(experiment);
  assert(experiment->IsValid());
  if (ui->box_show_calculation->isChecked()) { ShowCalculation(experiment); }
  if (ui->box_show_graphs->isChecked()) { ShowGraph(experiment); }
  if (ui->box_show_statistics->isChecked()) { ShowStatistics(experiment); }
  if (ui->box_show_table->isChecked()) { ShowTable(experiment); }
}


void ribi::kalman::QtKalmanFiltererMainDialog::SetShowCalculation(const bool do_show)
{
  ui->box_show_calculation->setChecked(do_show);
}

void ribi::kalman::QtKalmanFiltererMainDialog::SetShowGraph(const bool do_show)
{
  ui->box_show_graphs->setChecked(do_show);
}

void ribi::kalman::QtKalmanFiltererMainDialog::SetShowStatistics(const bool do_show)
{
  ui->box_show_statistics->setChecked(do_show);
}

void ribi::kalman::QtKalmanFiltererMainDialog::SetShowTable(const bool do_show)
{
  ui->box_show_table->setChecked(do_show);
}

void ribi::kalman::QtKalmanFiltererMainDialog::ShowCalculation(
  const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(m_to_delete_at_new_run.empty());
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
      + "QDialog { background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 ";
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
    m_to_delete_at_new_run.push_back(calculation_dialog); //Store for delettion
    assert(ui->scroll_area_calculation_contents->layout());
    ui->scroll_area_calculation_contents->layout()->addWidget(calculation_dialog.get());
  }
}

void ribi::kalman::QtKalmanFiltererMainDialog::ShowGraph(const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
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
    #if QWT_VERSION >= 0x060100 || !WIN32
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

void ribi::kalman::QtKalmanFiltererMainDialog::ShowStatistics(const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(experiment->IsValid());
  //Make fresh graph section
  assert(!ui->scroll_area_statistics_contents->layout());
  ui->scroll_area_statistics_contents->setLayout(new QVBoxLayout);
  assert(ui->scroll_area_statistics_contents->layout());

  //Create the table widget
  const int state_size = boost::numeric_cast<int>(experiment->GetStateNames().size());
  const int n_rows = state_size;
  const int n_cols = 1;

  QtCopyAllTableWidget * const table = new QtCopyAllTableWidget;

  //Store for deletion
  {
    const boost::shared_ptr<QWidget> p(table);
    assert(p);
    m_to_delete_at_new_run.push_back(p);
  }

  table->setToolTip("Display the average squared error for every state: ((p-r)^2)/t");
  table->setColumnCount(n_cols);
  table->setRowCount(n_rows);
  table->setAlternatingRowColors(true);
  assert(ui->scroll_area_statistics_contents->layout());
  ui->scroll_area_statistics_contents->layout()->addWidget(table);

  //Layout the data for putting in table
  const std::vector<double> vs = ExtractAverageSquaredError(experiment);
  //assert(!vs.empty()); //vs can be empty

  //Leave if there is no data to put in table
  if (vs.empty()) return;

  //Put descriptions in horizontal header
  for (int col=0; col!=n_cols; ++col)
  {
    QTableWidgetItem * const item = new QTableWidgetItem;
    const std::string text = col == 0 ? "State name" : "Average squared error";
    item->setText(text.c_str());
    table->setHorizontalHeaderItem(col,item);
  }
  //Put state names in vertical header
  for (int row=0; row!=state_size; ++row)
  {
    assert(row < static_cast<int>(experiment->GetStateNames().size()));
    const std::string name = experiment->GetStateNames()[row];
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(name.c_str());
    table->setVerticalHeaderItem(row,item);
  }
  //Put the average squared error in place
  for (int col=0; col!=n_cols; ++col)
  {
    assert(n_cols == 1);
    for (int row=0; row!=state_size; ++row)
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(vs[row]));
      table->setItem(row,col,item);
    }
  }
}


void ribi::kalman::QtKalmanFiltererMainDialog::ShowTable(const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(experiment->IsValid());
  //Make fresh graph section
  assert(!ui->scroll_area_table_contents->layout());
  ui->scroll_area_table_contents->setLayout(new QVBoxLayout);
  assert(ui->scroll_area_table_contents->layout());

  //Create the table widget
  const int state_size = boost::numeric_cast<int>(experiment->GetStateNames().size());
  const int n_cols = state_size * 4; //Display 4 values per state: real, measured, predicted and input

  //n_timesteps may differ from n_timesteps_desired, because in the actual experiment
  //the innovation variance may become degenerate
  //! Do not use GetInputs() its size: this size is always set to the maximum
  //  duration of the experiment
  const int n_timesteps = boost::numeric_cast<int>(experiment->GetRealStates().size());
  const int n_rows = n_timesteps;

  QtCopyAllTableWidget * const table = new QtCopyAllTableWidget;

  //Store for deletion
  {
    const boost::shared_ptr<QWidget> p(table);
    assert(p);
    m_to_delete_at_new_run.push_back(p);
  }

  table->setColumnCount(n_cols);
  table->setRowCount(n_rows);
  table->setAlternatingRowColors(true);
  assert(ui->scroll_area_table_contents->layout());
  ui->scroll_area_table_contents->layout()->addWidget(table);

  assert(n_timesteps == boost::numeric_cast<int>(experiment->GetRealStates().size()));
  assert(n_timesteps == boost::numeric_cast<int>(experiment->GetPredictedStates().size()));
  assert(n_timesteps == boost::numeric_cast<int>(experiment->GetMeasuredStates().size()));

  //Layout the data for putting in table
  const std::vector<std::vector<double> > vs = CreateData(
    experiment->GetRealStates(),
    experiment->GetMeasuredStates(),
    experiment->GetPredictedStates(),
    experiment->GetInputs());
  //assert(!vs.empty()); //vs can be empty

  //Leave if there is no data to put in table
  if (vs.empty()) return;

  //Put state descriptions in horizontal header
  for (int col=0; col!=n_cols; ++col)
  {
    QTableWidgetItem * const item = new QTableWidgetItem;
    const int state_index = col / 4;
    assert(state_index < boost::numeric_cast<int>(experiment->GetStateNames().size()));
    const std::string text_state = experiment->GetStateNames()[state_index];
    std::string text_extra;
    switch (col % 4)
    {
      case 0: text_extra = "_real"; break;
      case 1: text_extra = "_measured"; break;
      case 2: text_extra = "_predicted"; break;
      case 3: text_extra = "_input"; break;
    }
    const std::string text = text_state + text_extra;
    item->setText(text.c_str());
    table->setHorizontalHeaderItem(col,item);
  }
  //Put time series in vertical header
  for (int row=0; row!=n_timesteps; ++row)
  {
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(QString::number(row));
    table->setVerticalHeaderItem(row,item);
  }
  for (int col=0; col!=n_cols; ++col)
  {
    assert(col < boost::numeric_cast<int>(vs.size()));
    const std::vector<double>& v = vs[col];
    assert(n_timesteps == boost::numeric_cast<int>(v.size()));
    for (int row=0; row!=n_timesteps; ++row)
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(v[row]));
      table->setItem(row,col,item);
    }
  }
}

#ifndef NDEBUG
void ribi::kalman::QtKalmanFiltererMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::kalman::QtKalmanFiltererMainDialog::Create();
  }
  const TestTimer test_timer(__func__,__FILE__,2.0);
  const bool verbose{false};
  //TestTimer::SetMaxCnt(2);
  {
    if (verbose) { TRACE("ribi::kalman::QtKalmanFiltererMainDialog::Test: Create self"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
      const boost::shared_ptr<QtKalmanFiltererMainDialog> d
        = ribi::kalman::QtKalmanFiltererMainDialog::Create();
      assert(d);
      assert(d->m_model);
      d->m_model->SetNumberOfTimesteps(1); //Otherwise these tests take too long
      d->SetShowCalculation(true);
      d->SetShowGraph(true);
      d->SetShowStatistics(true);
      d->SetShowTable(true);
      d->on_button_start_clicked();
    }
    if (verbose) { TRACE("ribi::kalman::QtKalmanFiltererMainDialog::Test: (1/2) Click on example x and write these to a DokuWiki file"); }
    if (verbose) { TRACE("ribi::kalman::QtKalmanFiltererMainDialog::Test: (2/2) Click on example y and read the file from x"); }
    {
      //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
      const boost::shared_ptr<QtKalmanFiltererMainDialog> d
        = ribi::kalman::QtKalmanFiltererMainDialog::Create();
      assert(d);
      assert(d->m_model);
      assert(d->m_experiment_dialog);
      d->m_model->SetNumberOfTimesteps(2); //Otherwise these tests take too long
      const std::string filename = "TempQtKalmanFiltererMainDialogTest.txt";
      const int n_examples = 1; //Can be changed to 6
      for (int x = 0; x!= n_examples; ++x)
      {
        //1) Click on example x and write these to a DokuWiki file
        {
          d->m_experiment_dialog->GetExamplesDialog()->EmitExample(x);
          d->m_model->SetNumberOfTimesteps(2); //Otherwise these tests take too long
          d->m_experiment_dialog->SaveToDokuWiki(filename);
        }
        for (int y = 0; y!= n_examples; ++y)
        {
          //2) Click on example y and read the file from x
          d->m_experiment_dialog->GetExamplesDialog()->EmitExample(y);
          d->m_model->SetNumberOfTimesteps(2); //Otherwise these tests take too long
          d->m_experiment_dialog->LoadFromDokuWiki(filename);
        }
      }
      //Delete file
      std::remove(filename.c_str());
    }
  }
}
#endif

void ribi::kalman::QtKalmanFiltererMainDialog::on_tab_context_currentChanged(int index)
{
  assert(index == ui->tab_context->currentIndex());
  if (index == 0)
  {
    #ifndef DISABLE_QWEBVIEW
    //Render HTML when user really wants to see it
    const QString s = ui->edit_context->toPlainText();
    ui->web_view_context->setHtml(s);
    #endif
  }
}

void ribi::kalman::QtKalmanFiltererMainDialog::OnNewContext(const std::string context)
{
  if (ui->edit_context->toPlainText().toStdString() != context)
  {
    ui->edit_context->setPlainText(context.c_str());
    if (ui->tab_context->currentIndex() == 0)
    {
      #ifndef DISABLE_QWEBVIEW
      //Only display HTML when visible
      ui->web_view_context->setHtml(context.c_str());
      #endif
    }
    assert(ui->edit_context->toPlainText().toStdString() == context);
  }
  assert(ui->edit_context->toPlainText().toStdString() == context);

}

void ribi::kalman::QtKalmanFiltererMainDialog::on_edit_context_textChanged()
{
  this->m_model->SetContext(ui->edit_context->toPlainText().toStdString());
}
