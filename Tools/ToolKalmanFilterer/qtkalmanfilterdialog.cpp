#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkalmanfilterdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include "matrix.h"
#include "qtmatrix.h"
#include "testtimer.h"
#include "standardkalmanfilter.h"
#include "standardkalmanfilterfactory.h"
#include "steadystatekalmanfilter.h"
#include "kalmanfilterparameter.h"
#include "kalmanfiltertypes.h"
#include "fixedlagsmootherkalmanfilter.h"
#include "steadystatekalmanfilterfactory.h"
#include "kalmanfilterexperimentparameter.h"
#include "trace.h"
#include "ui_qtkalmanfilterdialog.h"

#pragma GCC diagnostic pop

ribi::kalman::QtKalmanFilterDialog::QtKalmanFilterDialog(const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    m_signal_kalman_filter_type_changed{},
    ui(new Ui::QtKalmanFilterDialog),
    m_model{model},
    m_parameters{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_model);
  ui->setupUi(this);

  //Create the map
  {
    const std::vector<KalmanFilterParameterType> v = this->GetParameterTypes();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(i < v.size());

      const KalmanFilterParameterType type = v[i];

      QtKalmanFiltererParameterDialog * const dialog
        = new QtKalmanFiltererParameterDialog(
          KalmanFilterParameter().ToName(type),
          KalmanFilterParameter().ToDescription(type),
          m_model->Find( KalmanFilterExperimentParameter().ConvertToKalmanFilterExperimentParameter(v[i]) )
        );
      assert(dialog);

      //Add to map
      m_parameters.insert(std::make_pair(type,dialog));

      //Add to dialog
      assert(this->layout());
      this->layout()->addWidget(dialog);

    }
    assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(KalmanFilterParameterType::n_parameters)
      && "All parameters must be in");
  }

  this->setFocusPolicy(Qt::NoFocus);
  this->on_box_filter_type_currentIndexChanged(0);
  //assert(this->GetKalmanFilter() && "Can get an empty Kalman filter, with all sizes equal to zero");

  m_model->m_signal_kalman_filter_type_changed.connect(
    boost::bind(&ribi::kalman::QtKalmanFilterDialog::SetKalmanFilterType,this,boost::lambda::_1));
}

ribi::kalman::QtKalmanFilterDialog::~QtKalmanFilterDialog() noexcept
{
  delete ui;
}

ribi::kalman::KalmanFilterType ribi::kalman::QtKalmanFilterDialog::GetKalmanFilterType() const
{
  switch (ui->box_filter_type->currentIndex())
  {
    case 0: return KalmanFilterType::standard;
    case 1: return KalmanFilterType::steady_state;
    case 2: return KalmanFilterType::fixed_lag_smoother;
    default:
      TRACE(ui->box_filter_type->currentIndex());
      assert(!"Unimplemented ComboBox index");
      throw std::logic_error(__func__);
  }
}


const std::vector<ribi::kalman::KalmanFilterParameterType> ribi::kalman::QtKalmanFilterDialog::GetParameterTypes() const
{
  const std::vector<KalmanFilterParameterType> v
    =
    {
      KalmanFilterParameterType::initial_state_estimate,             //x
      KalmanFilterParameterType::initial_covariance_estimate,        //P
      KalmanFilterParameterType::state_transition,                   //A
      KalmanFilterParameterType::control,                            //B
      KalmanFilterParameterType::observation,                        //H
      KalmanFilterParameterType::estimated_optimal_kalman_gain,      //K
      KalmanFilterParameterType::estimated_process_noise_covariance, //Q
      KalmanFilterParameterType::estimated_measurement_noise         //R
    };
  assert(v.size() == KalmanFilterParameter().GetAll().size());
  return v;
}

void ribi::kalman::QtKalmanFilterDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;
  QDialog::keyPressEvent(event);
}


void ribi::kalman::QtKalmanFilterDialog::SetKalmanFilterType(const KalmanFilterType new_type)
{
  if (this->GetKalmanFilterType() != new_type)
  {

    switch (new_type)
    {
      case KalmanFilterType::standard:
        assert(ui->box_filter_type->count() > 0); //Otherwise index -1 will be set
        ui->box_filter_type->setCurrentIndex(0);
        break;
      case KalmanFilterType::steady_state:
        assert(ui->box_filter_type->count() > 1); //Otherwise index -1 will be set
        ui->box_filter_type->setCurrentIndex(1);
        break;
      case KalmanFilterType::fixed_lag_smoother:
        assert(ui->box_filter_type->count() > 2); //Otherwise index -1 will be set
        ui->box_filter_type->setCurrentIndex(2);
        break;
      case KalmanFilterType::n_types:
        assert(!"Unimplemented KalmanFilterType");
        throw std::logic_error(__func__);
    }
    assert(this->GetKalmanFilterType() == new_type);
  }
  assert(this->GetKalmanFilterType() == new_type);
}

void ribi::kalman::QtKalmanFilterDialog::on_button_calculate_optimal_kalman_gain_steady_state_clicked()
{
  m_model->CalculateOptimalEstimatedKalmanGain();
}

void ribi::kalman::QtKalmanFilterDialog::on_box_filter_type_currentIndexChanged(int)
{
  //Update the GUI
  switch (this->GetKalmanFilterType())
  {
    case KalmanFilterType::standard:
    {
      const auto j = m_parameters.end();
      for (auto i = m_parameters.begin(); i!=j; ++i)
      {
        ((*i).second)->setVisible(StandardKalmanFilterParameters::HasParameterType((*i).first));
      }
      ui->box_estimated_lag->setVisible(false);
      ui->label_estimated_lag->setVisible(false);
      ui->button_calculate_optimal_kalman_gain_steady_state->setVisible(false);
    }
    break;
    case KalmanFilterType::steady_state:
    {
      const auto j = m_parameters.end();
      for (auto i = m_parameters.begin(); i!=j; ++i)
      {
        ((*i).second)->setVisible(SteadyStateKalmanFilterParameters::HasParameterType((*i).first));
      }
      ui->box_estimated_lag->setVisible(false);
      ui->label_estimated_lag->setVisible(false);
      ui->button_calculate_optimal_kalman_gain_steady_state->setVisible(true);
    }
    break;
    case KalmanFilterType::fixed_lag_smoother:
    {
      const auto j = m_parameters.end();
      for (auto i = m_parameters.begin(); i!=j; ++i)
      {
        ((*i).second)->setVisible(FixedLagSmootherKalmanFilterParameters::HasParameterType((*i).first));
      }
      ui->box_estimated_lag->setVisible(true);
      ui->label_estimated_lag->setVisible(true);
      ui->button_calculate_optimal_kalman_gain_steady_state->setVisible(false);
    }
    break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented Kalman filter type");
  }

  //Notify the model
  m_model->SetKalmanFilterType(this->GetKalmanFilterType());

  m_signal_kalman_filter_type_changed(this->GetKalmanFilterType());
}

#ifndef NDEBUG
void ribi::kalman::QtKalmanFilterDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  KalmanFilterParameter();
  KalmanFilterExperimentParameter();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
