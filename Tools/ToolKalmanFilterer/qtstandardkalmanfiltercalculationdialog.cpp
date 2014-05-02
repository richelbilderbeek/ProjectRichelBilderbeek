#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtstandardkalmanfiltercalculationdialog.h"

#include <boost/lexical_cast.hpp>

#include "matrix.h"
#include "qtmatrix.h"
#include "standardkalmanfilter.h"
#include "standardkalmanfiltercalculationelements.h"
#include "standardkalmanfilterparameters.h"
#include "ui_qtstandardkalmanfiltercalculationdialog.h"

#pragma GCC diagnostic pop

ribi::kalman::QtStandardKalmanFilterCalculationDialog::QtStandardKalmanFilterCalculationDialog(QWidget *parent) :
  QtKalmanFilterCalculationDialog(parent),
  ui(new Ui::QtStandardKalmanFilterCalculationDialog)
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

ribi::kalman::QtStandardKalmanFilterCalculationDialog::~QtStandardKalmanFilterCalculationDialog() noexcept
{
  delete ui;
}

const std::vector<QTableWidget *> ribi::kalman::QtStandardKalmanFilterCalculationDialog::CollectMatrices() const
{
  std::vector<QTableWidget *> v;
  v.push_back(ui->table_control_1);
  v.push_back(ui->table_covariance_predicted_2);
  v.push_back(ui->table_covariance_predicted_4);
  v.push_back(ui->table_covariance_predicted_5);
  v.push_back(ui->table_covariance_predicted_7);
  v.push_back(ui->table_estimated_measurement_noise);
  v.push_back(ui->table_estimated_process_noise);
  v.push_back(ui->table_identity_matrix);
  v.push_back(ui->table_innovation_covariance_4);
  v.push_back(ui->table_innovation_covariance_5_inverted);
  v.push_back(ui->table_kalman_gain_5);
  v.push_back(ui->table_kalman_gain_6);
  v.push_back(ui->table_kalman_gain_7);
  v.push_back(ui->table_new_covariance);
  v.push_back(ui->table_observation_3);
  v.push_back(ui->table_observation_4);
  v.push_back(ui->table_observation_4_transposed);
  v.push_back(ui->table_observation_5_transposed);
  v.push_back(ui->table_observation_7);
  v.push_back(ui->table_previous_covariance_estimate);
  v.push_back(ui->table_state_transition_1);
  v.push_back(ui->table_state_transition_1_2);
  v.push_back(ui->table_state_transition_2_transposed);
  return v;
}

const std::vector<QTableWidget *> ribi::kalman::QtStandardKalmanFilterCalculationDialog::CollectVectors() const
{
  std::vector<QTableWidget *> v;
  v.push_back(ui->table_innovation_3);
  v.push_back(ui->table_innovation_6);
  v.push_back(ui->table_input);
  v.push_back(ui->table_measurement);
  v.push_back(ui->table_new_state_estimate);
  v.push_back(ui->table_previous_state_estimate);
  v.push_back(ui->table_state_predicted_1);
  v.push_back(ui->table_state_predicted_3);
  v.push_back(ui->table_state_predicted_6);
  return v;
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetStandardCalculationElements(
  const boost::shared_ptr<const StandardKalmanFilterCalculationElements>& calculation_elements)
{
  assert(calculation_elements);
  this->SetInnovation(calculation_elements->GetInnovation());
  this->SetInnovationCovariance(calculation_elements->GetInnovationCovariance());
  this->SetKalmanGain(calculation_elements->GetKalmanGain());
  this->SetMeasurement(calculation_elements->GetMeasurement());
  this->SetPredictedCovariance(calculation_elements->GetPredicatedCovariance());
  this->SetPredictedState(calculation_elements->GetPredictedState());
  this->SetPreviousCovarianceEstimate(calculation_elements->GetPreviousCovarianceEstimate());
  this->SetPreviousStateEstimate(calculation_elements->GetPreviousState());
  this->SetUpdatedCovariance(calculation_elements->GetUpdatedCovariance());
  this->SetUpdatedState(calculation_elements->GetUpdatedState());
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetControl(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_control_1);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetIdentityMatrix(const int sz)
{
  QtMatrix::MatrixToTable(
    boost::numeric::ublas::identity_matrix<double>(sz),
    ui->table_identity_matrix);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetInnovation(const boost::numeric::ublas::vector<double>& m)
{
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_innovation_3);
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_innovation_6);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetInnovationCovariance(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_innovation_covariance_4);
  QtMatrix::MatrixToTable(
    Matrix::Inverse(m),
    ui->table_innovation_covariance_5_inverted);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetInput(const boost::numeric::ublas::vector<double>& m)
{
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_input);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetKalmanGain(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_kalman_gain_5);
  QtMatrix::MatrixToTable(m,ui->table_kalman_gain_6);
  QtMatrix::MatrixToTable(m,ui->table_kalman_gain_7);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetMeasurement(const boost::numeric::ublas::vector<double>& m)
{
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_measurement);
}


void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetMeasurementNoiseEstimate(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_estimated_measurement_noise);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetObservation(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_observation_3);
  QtMatrix::MatrixToTable(m,ui->table_observation_4);
  QtMatrix::MatrixToTable(
    boost::numeric::ublas::trans(m),
    ui->table_observation_4_transposed);
  QtMatrix::MatrixToTable(
    boost::numeric::ublas::trans(m),
    ui->table_observation_5_transposed);
  QtMatrix::MatrixToTable(m,ui->table_observation_7);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetPredictedCovariance(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_covariance_predicted_2);
  QtMatrix::MatrixToTable(m,ui->table_covariance_predicted_4);
  QtMatrix::MatrixToTable(m,ui->table_covariance_predicted_5);
  QtMatrix::MatrixToTable(m,ui->table_covariance_predicted_7);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetPredictedState(const boost::numeric::ublas::vector<double>& m)
{
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_state_predicted_1);
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_state_predicted_3);
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_state_predicted_6);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetPreviousCovarianceEstimate(
  const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_previous_covariance_estimate);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetPreviousStateEstimate(
  const boost::numeric::ublas::vector<double>& m)
{
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_previous_state_estimate);
}


void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetProcessNoiseEstimate(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_estimated_process_noise);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetStateNames(const std::vector<std::string>& names)
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
        table->verticalHeader()->length()   + 2 + table->horizontalHeader()->height());
      //table->setFixedSize(
      //  table->horizontalHeader()->length() + 2 + table->verticalHeader()->width(),
      //  table->verticalHeader()->length()   + 2 + table->horizontalHeader()->height());
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
        table->verticalHeader()->length()   + 2 + table->horizontalHeader()->height());
      //table->setFixedSize(
      //  table->horizontalHeader()->length() + 2 + table->verticalHeader()->width(),
      //  table->verticalHeader()->length()   + 2 + table->horizontalHeader()->height());
    }
  }
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetStateTransition(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_state_transition_1);
  QtMatrix::MatrixToTable(m,ui->table_state_transition_1_2);
  QtMatrix::MatrixToTable(
    boost::numeric::ublas::trans(m),
    ui->table_state_transition_2_transposed);
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetTime(const int i)
{
  const std::string s = "Time: " + boost::lexical_cast<std::string>(i);
  ui->label_time->setText(s.c_str());
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::ShowCalculation(
  const int i,
  const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
{
  assert(experiment);
  assert(experiment->GetKalmanFilter());
  assert(this->GetType() == experiment->GetKalmanFilter()->GetType());
  assert(this->GetType() == experiment->GetKalmanFilter()->GetParameters()->GetType());
  assert(i < boost::numeric_cast<int>(experiment->GetCalculationElements().size()));

  const boost::shared_ptr<const StandardKalmanFilterCalculationElements> calculation_elements(
    boost::dynamic_pointer_cast<const StandardKalmanFilterCalculationElements>(experiment->GetCalculationElements()[i]));
  assert(calculation_elements);

  this->SetStandardCalculationElements(calculation_elements);

  const boost::shared_ptr<const StandardKalmanFilterParameters> parameters(
    boost::dynamic_pointer_cast<const StandardKalmanFilterParameters>(experiment->GetKalmanFilter()->GetParameters()));
  assert(parameters);

  this->SetControl(parameters->GetControl());
  this->SetIdentityMatrix(boost::numeric_cast<int>(experiment->GetStateNames().size()));
  this->SetInput(experiment->GetInputs().at(i));
  this->SetMeasurementNoiseEstimate(parameters->GetEstimatedMeasurementNoise());
  this->SetObservation(parameters->GetObservation());
  this->SetProcessNoiseEstimate(parameters->GetEstimatedProcessNoiseCovariance());
  this->SetStateNames(experiment->GetStateNames());
  this->SetStateTransition(parameters->GetStateTransition());
}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetUpdatedCovariance(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_new_covariance);

}

void ribi::kalman::QtStandardKalmanFilterCalculationDialog::SetUpdatedState(const boost::numeric::ublas::vector<double>& m)
{
  QtMatrix::UblasVectorDoubleToTable(m,ui->table_new_state_estimate);
}
