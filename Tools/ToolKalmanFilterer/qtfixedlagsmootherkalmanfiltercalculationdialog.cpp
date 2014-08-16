#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtfixedlagsmootherkalmanfiltercalculationdialog.h"

#include <boost/lexical_cast.hpp>

#include "matrix.h"
#include "qtmatrix.h"
#include "fixedlagsmootherkalmanfilterparameters.h"
#include "kalmanfiltercalculationelements.h"
#include "ui_qtfixedlagsmootherkalmanfiltercalculationdialog.h"

#pragma GCC diagnostic pop

ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::QtFixedLagSmootherKalmanFilterCalculationDialog(QWidget *parent) :
  QtKalmanFilterCalculationDialog(parent),
  ui(new Ui::QtFixedLagSmootherKalmanFilterCalculationDialog)
{
  ui->setupUi(this);


  this->setStyleSheet(
   "QWidget#widget_1 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #fbb, stop: 1 #fff);"
    "} "
   "QWidget#widget_2 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #ffb, stop: 1 #fff);"
    "} "
   "QWidget#widget_3 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bfb, stop: 1 #fff);"
    "} "
   "QWidget#widget_4 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bff, stop: 1 #fff);"
    "} "
   "QWidget#widget_5 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bbf, stop: 1 #fff);"
    "} "
   "QWidget#widget_6 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #fbf, stop: 1 #fff);"
    "} "
   "QWidget#widget_7 { "
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #fff, stop: 1 #fff);"
    "} "
  );
}

ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::~QtFixedLagSmootherKalmanFilterCalculationDialog() noexcept
{
  delete ui;
}

const std::vector<QTableWidget *> ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::CollectMatrices() const
{
  std::vector<QTableWidget *> v;
  /*
  v.push_back(ui->table_control);
  v.push_back(ui->table_gain_1);
  v.push_back(ui->table_gain_2);
  v.push_back(ui->table_observation_model);
  v.push_back(ui->table_state_transition);
  */
  return v;
}

const std::vector<QTableWidget *> ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::CollectVectors() const
{
  std::vector<QTableWidget *> v;
  /*
  v.push_back(ui->table_input);
  v.push_back(ui->table_measurement);
  v.push_back(ui->table_previous_state_estimate);
  v.push_back(ui->table_state_predicted);
  */
  return v;
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetFixedLagSmootherCalculationElements(
  const boost::shared_ptr<const FixedLagSmootherKalmanFilterCalculationElements>& calculation_elements)
{
  assert(calculation_elements);
  this->SetMeasurement(calculation_elements->GetMeasurement());
  this->SetPredictedState(calculation_elements->GetUpdatedState());
  this->SetPreviousStateEstimate(calculation_elements->GetPreviousState());
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetControl(const boost::numeric::ublas::matrix<double>& )
{
  //QtMatrix::MatrixToTable(m,ui->table_control);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetInput(const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_input);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetEstimatedOptimalKalmanGain(const boost::numeric::ublas::matrix<double>& )
{
  //QtMatrix::MatrixToTable(m,ui->table_gain_1);
  //QtMatrix::MatrixToTable(m,ui->table_gain_2);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetMeasurement(const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_measurement);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetObservation(const boost::numeric::ublas::matrix<double>& )
{
  //QtMatrix::MatrixToTable(m,ui->table_observation_model);
}


void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetPredictedState(const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_state_predicted);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetPreviousStateEstimate(
  const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_previous_state_estimate);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetStateNames(const std::vector<std::string>& names)
{
  const int n = boost::numeric_cast<int>(names.size());
  //Matrices
  {
    const std::vector<QTableWidget *> v = CollectMatrices();
    const std::size_t sz = v.size();
    for (std::size_t i = 0; i!=sz; ++i)
    {
      QTableWidget * const table = v[i];
      assert(table);
      table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

      table->setColumnCount(boost::numeric_cast<int>(names.size()));
      table->setRowCount(boost::numeric_cast<int>(names.size()));
      assert(table->columnCount() == boost::numeric_cast<int>(names.size()));
      assert(table->rowCount() == boost::numeric_cast<int>(names.size()));
      for (int j = 0; j!=n; ++j)
      {
        {
          QTableWidgetItem * const item = new QTableWidgetItem;
          item->setText(names[j].c_str());
          table->setVerticalHeaderItem(j,item);
        }
        {
          QTableWidgetItem * const item = new QTableWidgetItem;
          item->setText(names[j].c_str());
          table->setHorizontalHeaderItem(j,item);
        }
      }
      table->resizeColumnsToContents();
      table->resizeRowsToContents();
      table->update();
      table->setFixedHeight(
        table->verticalHeader()->length()   + 2 + table->horizontalHeader()->height()
      );
    }
  }
  //Vectors
  {
    const std::vector<QTableWidget *> v = CollectVectors();

    const std::size_t sz = v.size();
    for (std::size_t i = 0; i!=sz; ++i)
    {
      QTableWidget * const table = v[i];
      table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

      table->setRowCount(boost::numeric_cast<int>(names.size()));
      assert(table->rowCount() == boost::numeric_cast<int>(names.size()));
      //Remove top text
      {
        QTableWidgetItem * const item = new QTableWidgetItem;
        item->setText(" ");
        table->setHorizontalHeaderItem(0,item);
      }

      for (int j = 0; j!=n; ++j)
      {
        QTableWidgetItem * const item = new QTableWidgetItem;
        item->setText(names[j].c_str());
        table->setVerticalHeaderItem(j,item);
      }
      table->resizeColumnsToContents();
      table->resizeRowsToContents();
      table->setFixedHeight(
        table->verticalHeader()->length()   + 2 + table->horizontalHeader()->height()
      );
    }
  }
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetStateTransition(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_state_transition);
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::SetTime(const int i)
{
  const std::string s = "Time: " + boost::lexical_cast<std::string>(i);
  ui->label_time->setText(s.c_str());
}

void ribi::kalman::QtFixedLagSmootherKalmanFilterCalculationDialog::ShowCalculation(const int i, const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(experiment->GetKalmanFilter());
  assert(this->GetType() == experiment->GetKalmanFilter()->GetType());
  assert(this->GetType() == experiment->GetKalmanFilter()->GetParameters()->GetType());

  assert(i < boost::numeric_cast<int>(experiment->GetCalculationElements().size()));

  const boost::shared_ptr<const FixedLagSmootherKalmanFilterCalculationElements> calculation_elements(
    boost::dynamic_pointer_cast<const FixedLagSmootherKalmanFilterCalculationElements>(experiment->GetCalculationElements()[i]));
  assert(calculation_elements);
  this->SetFixedLagSmootherCalculationElements(calculation_elements);

  const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters> parameters(
    boost::dynamic_pointer_cast<const FixedLagSmootherKalmanFilterParameters>(experiment->GetKalmanFilter()->GetParameters()));
  assert(parameters);

  this->SetControl(parameters->GetControl());
  this->SetInput(experiment->GetInputs().at(i));
  this->SetObservation(parameters->GetObservation());
  this->SetStateNames(experiment->GetStateNames());
  this->SetStateTransition(parameters->GetStateTransition());
}
