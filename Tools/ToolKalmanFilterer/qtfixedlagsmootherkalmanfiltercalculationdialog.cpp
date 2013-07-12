#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtfixedlagsmootherkalmanfiltercalculationdialog.h"

#include <boost/lexical_cast.hpp>

#include "matrix.h"
#include "qtmatrix.h"
#include "fixedlagsmootherkalmanfilterparameters.h"
#include "kalmanfiltercalculationelements.h"
#include "ui_qtfixedlagsmootherkalmanfiltercalculationdialog.h"

#pragma GCC diagnostic pop

QtFixedLagSmootherKalmanFilterCalculationDialog::QtFixedLagSmootherKalmanFilterCalculationDialog(QWidget *parent) :
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

QtFixedLagSmootherKalmanFilterCalculationDialog::~QtFixedLagSmootherKalmanFilterCalculationDialog()
{
  delete ui;
}

const std::vector<QTableWidget *> QtFixedLagSmootherKalmanFilterCalculationDialog::CollectMatrices() const
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

const std::vector<QTableWidget *> QtFixedLagSmootherKalmanFilterCalculationDialog::CollectVectors() const
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

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetFixedLagSmootherCalculationElements(
  const boost::shared_ptr<const FixedLagSmootherKalmanFilterCalculationElements>& calculation_elements)
{
  assert(calculation_elements);
  this->SetMeasurement(calculation_elements->GetMeasurement());
  this->SetPredictedState(calculation_elements->GetUpdatedState());
  this->SetPreviousStateEstimate(calculation_elements->GetPreviousState());
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetControl(const boost::numeric::ublas::matrix<double>& )
{
  //QtMatrix::MatrixToTable(m,ui->table_control);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetInput(const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_input);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetEstimatedOptimalKalmanGain(const boost::numeric::ublas::matrix<double>& )
{
  //QtMatrix::MatrixToTable(m,ui->table_gain_1);
  //QtMatrix::MatrixToTable(m,ui->table_gain_2);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetMeasurement(const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_measurement);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetObservation(const boost::numeric::ublas::matrix<double>& )
{
  //QtMatrix::MatrixToTable(m,ui->table_observation_model);
}


void QtFixedLagSmootherKalmanFilterCalculationDialog::SetPredictedState(const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_state_predicted);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetPreviousStateEstimate(
  const boost::numeric::ublas::vector<double>& )
{
  //QtMatrix::UblasVectorDoubleToTable(m,ui->table_previous_state_estimate);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetStateNames(const std::vector<std::string>& names)
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

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetStateTransition(const boost::numeric::ublas::matrix<double>& m)
{
  QtMatrix::MatrixToTable(m,ui->table_state_transition);
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::SetTime(const int i)
{
  const std::string s = "Time: " + boost::lexical_cast<std::string>(i);
  ui->label_time->setText(s.c_str());
}

void QtFixedLagSmootherKalmanFilterCalculationDialog::ShowCalculation(const int i, const boost::shared_ptr<const KalmanFilterExperiment>& experiment)
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
  //this->SetEstimatedOptimalKalmanGain(parameters->GetEstimatedOptimalKalmanGain());
  this->SetStateNames(experiment->GetStateNames());
  this->SetStateTransition(parameters->GetStateTransition());
}
