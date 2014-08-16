#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtwhitenoisesystemparametersdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QKeyEvent>
#include <QVBoxLayout>

#include "gapsfilledwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystemfactory.h"
#include "kalmanfilterexperimentparameter.h"
#include "laggedwhitenoisesystem.h"
#include "laggedwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystemparameters.h"
#include "matrix.h"
#include "testtimer.h"
#include "qtkalmanfiltererparameterdialog.h"
#include "qtmatrix.h"
#include "qtublasvectorintmodel.h"
#include "standardwhitenoisesystem.h"
#include "standardwhitenoisesystemfactory.h"
#include "standardwhitenoisesystemparameters.h"
#include "trace.h"
#include "ui_qtwhitenoisesystemparametersdialog.h"
#include "whitenoisesystemparameter.h"
#include "whitenoisesystemparametertype.h"

#pragma GCC diagnostic pop

ribi::kalman::QtWhiteNoiseSystemParametersDialog::QtWhiteNoiseSystemParametersDialog(
  const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtWhiteNoiseSystemParametersDialog),
    m_model{model},
    m_parameters{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  //Create the map
  {
    const std::vector<WhiteNoiseSystemParameterType> v = WhiteNoiseSystemParameter().GetAll();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(i < v.size());

      const WhiteNoiseSystemParameterType type = v[i];
      assert(type != WhiteNoiseSystemParameterType::n_parameters);
      QtKalmanFiltererParameterDialog * const dialog
        = new QtKalmanFiltererParameterDialog(
          WhiteNoiseSystemParameter().ToName(type),
          WhiteNoiseSystemParameter().ToDescription(type),
          m_model->Find( KalmanFilterExperimentParameter().ConvertToKalmanFilterExperimentParameter(v[i]) )
        );
      assert(dialog);

      //Add to map
      m_parameters.insert(std::make_pair(type,dialog));

      //Add to dialog
      assert(this->layout());
      this->layout()->addWidget(dialog);

    }
    assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(WhiteNoiseSystemParameterType::n_parameters)
      && "All parameters must be in");
  }

  //Fill the combo box with the types of white noise systems
  {
    assert(ui->box_white_noise_system_type->count() == 0);
    ui->box_white_noise_system_type->addItem("Standard white noise system");
    ui->box_white_noise_system_type->addItem("Lagged white noise system");
    ui->box_white_noise_system_type->addItem("Gaps-filled white noise system");
    assert(ui->box_white_noise_system_type->count() == static_cast<int>(WhiteNoiseSystemType::n_types));
  }

  this->setFocusPolicy(Qt::NoFocus);

  this->SetWhiteNoiseSystemType(m_model->CreateWhiteNoiseSystemParameters()->GetType());
  assert(m_model->CreateWhiteNoiseSystemParameters()->GetType() == this->GetWhiteNoiseSystemType());
  assert(m_model->CreateWhiteNoiseSystem() && "Obtain an empty white noise system (all components have size zero)");
}

ribi::kalman::QtWhiteNoiseSystemParametersDialog::~QtWhiteNoiseSystemParametersDialog() noexcept
{
  delete ui;
}

ribi::kalman::QtKalmanFiltererParameterDialog * ribi::kalman::QtWhiteNoiseSystemParametersDialog::Find(const WhiteNoiseSystemParameterType type)
{
  //Calls the const version of Find
  //To avoid duplication in const and non-const member functions
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines,
  //   and best practices. 2005. ISBN: 0-32-111358-6. Chapter 94: 'Avoid casting away const', item 'Exceptions'
  return const_cast<QtKalmanFiltererParameterDialog *>(const_cast<const QtWhiteNoiseSystemParametersDialog&>(*this).Find(type));
}

const ribi::kalman::QtKalmanFiltererParameterDialog * ribi::kalman::QtWhiteNoiseSystemParametersDialog::Find(const WhiteNoiseSystemParameterType type) const
{
  assert(m_model->CreateWhiteNoiseSystemParameters()->GetType() == this->GetWhiteNoiseSystemType());
  assert(m_parameters.find(type) != m_parameters.end());
  const QtKalmanFiltererParameterDialog * const table = (*m_parameters.find(type)).second;
  assert(table);
  return table;
}

int ribi::kalman::QtWhiteNoiseSystemParametersDialog::GetLag() const
{
  assert(ui->box_lag->value() >= 0);
  return ui->box_lag->value();
}

ribi::kalman::WhiteNoiseSystemType ribi::kalman::QtWhiteNoiseSystemParametersDialog::GetWhiteNoiseSystemType() const
{
  switch (ui->box_white_noise_system_type->currentIndex())
  {
    case 0: return WhiteNoiseSystemType::standard;
    case 1: return WhiteNoiseSystemType::lagged;
    case 2: return WhiteNoiseSystemType::gaps_filled;
    case -1:
      assert(!"ribi::kalman::QtWhiteNoiseSystemParametersDialog::GetWhiteNoiseSystemType: box_white_noise_system_type must be initialized");
      throw std::logic_error(__func__);
    default:
      assert(!"Unimplemented index of box_white_noise_system_type");
      throw std::logic_error(__func__);
  }
}

void ribi::kalman::QtWhiteNoiseSystemParametersDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;
  QDialog::keyPressEvent(event);
}

void ribi::kalman::QtWhiteNoiseSystemParametersDialog::on_box_white_noise_system_type_currentIndexChanged(int)
{
  //Notify the model
  m_model->SetWhiteNoiseSystemType(GetWhiteNoiseSystemType());
  assert(m_model->CreateWhiteNoiseSystemParameters()->GetType() == this->GetWhiteNoiseSystemType());

  switch (GetWhiteNoiseSystemType())
  {
    case WhiteNoiseSystemType::gaps_filled:
      ui->box_lag->setVisible(false);
      ui->label_lag->setVisible(false);
      assert(m_parameters.size() == WhiteNoiseSystemParameter().GetAll().size()
        && "m_parameters must be initialized");
      this->Find(WhiteNoiseSystemParameterType::measurement_frequency)->setVisible(true);
      break;
    case WhiteNoiseSystemType::lagged:
      ui->box_lag->setVisible(true);
      ui->label_lag->setVisible(true);
      assert(m_parameters.size() == WhiteNoiseSystemParameter().GetAll().size()
        && "m_parameters must be initialized");
      this->Find(WhiteNoiseSystemParameterType::measurement_frequency)->setVisible(false);
      break;
    case WhiteNoiseSystemType::standard:
      ui->box_lag->setVisible(false);
      ui->label_lag->setVisible(false);
      assert(m_parameters.size() == WhiteNoiseSystemParameter().GetAll().size()
        && "m_parameters must be initialized");
      this->Find(WhiteNoiseSystemParameterType::measurement_frequency)->setVisible(false);
      break;
    case WhiteNoiseSystemType::n_types:
      assert(!"Unimplemented WhiteNoiseSystemType");
  }

  assert(m_model->CreateWhiteNoiseSystemParameters()->GetType() == this->GetWhiteNoiseSystemType());
}

void ribi::kalman::QtWhiteNoiseSystemParametersDialog::on_box_lag_valueChanged(int arg1)
{
  m_model->SetLagReal(arg1);
  assert(m_model->CreateWhiteNoiseSystemParameters()->GetType() == this->GetWhiteNoiseSystemType());
}

void ribi::kalman::QtWhiteNoiseSystemParametersDialog::SetWhiteNoiseSystemType(const WhiteNoiseSystemType type)
{
  switch (type)
  {
    case WhiteNoiseSystemType::gaps_filled:
      ui->box_white_noise_system_type->setCurrentIndex(2);
      break;
    case WhiteNoiseSystemType::lagged:
      ui->box_white_noise_system_type->setCurrentIndex(1);
      break;
    case WhiteNoiseSystemType::standard:
      ui->box_white_noise_system_type->setCurrentIndex(0);
      break;
    case WhiteNoiseSystemType::n_types:
      assert(!"ribi::kalman::QtWhiteNoiseSystemParametersDialog::SetWhiteNoiseSystemType: use of n_types");
      throw std::logic_error("ribi::kalman::QtWhiteNoiseSystemParametersDialog::SetWhiteNoiseSystemType: use of n_types");
  }
  assert(this->GetWhiteNoiseSystemType() == type);
  assert(m_model->CreateWhiteNoiseSystemParameters()->GetType() == type);
}


#ifndef NDEBUG
void ribi::kalman::QtWhiteNoiseSystemParametersDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    GapsFilledWhiteNoiseSystemFactory();
    LaggedWhiteNoiseSystemFactory();
    QtKalmanFilterExperimentModel();
    WhiteNoiseSystemParameter();
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model(new QtKalmanFilterExperimentModel);
    { QtWhiteNoiseSystemParametersDialog d(model); }
    KalmanFilterExperimentParameter();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model(new QtKalmanFilterExperimentModel);
    assert(model);

    QtWhiteNoiseSystemParametersDialog d(model);
    d.ui->box_white_noise_system_type->setCurrentIndex(0);
    assert(d.GetWhiteNoiseSystemType() == WhiteNoiseSystemType::standard);
    assert(model->CreateWhiteNoiseSystemParameters()->GetType() == WhiteNoiseSystemType::standard);
    assert(!d.Find(WhiteNoiseSystemParameterType::measurement_frequency)->isVisible());
    assert(model->CreateWhiteNoiseSystemParameters());
    assert(model->CreateWhiteNoiseSystem());

    d.ui->box_white_noise_system_type->setCurrentIndex(1);
    assert(d.GetWhiteNoiseSystemType() == WhiteNoiseSystemType::lagged);
    assert(model->CreateWhiteNoiseSystemParameters()->GetType() == WhiteNoiseSystemType::lagged);
    assert(!d.Find(WhiteNoiseSystemParameterType::measurement_frequency)->isVisible());
    assert(model->CreateWhiteNoiseSystemParameters());
    assert(model->CreateWhiteNoiseSystem());

    d.ui->box_white_noise_system_type->setCurrentIndex(2);
    //assert(d.Find(WhiteNoiseSystemParameterType::measurement_frequency)->isVisible());
    assert(d.GetWhiteNoiseSystemType() == WhiteNoiseSystemType::gaps_filled);
    assert(model->Find(KalmanFilterExperimentParameterType::measurement_frequency));
    assert(model->CreateWhiteNoiseSystem());
    assert(model->CreateWhiteNoiseSystemParameters());
    assert(model->CreateWhiteNoiseSystemParameters()->GetType() == WhiteNoiseSystemType::gaps_filled);
  }
}
#endif
