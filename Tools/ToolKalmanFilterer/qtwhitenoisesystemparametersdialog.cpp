#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtwhitenoisesystemparametersdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QVBoxLayout>

#include "laggedwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystem.h"
#include "laggedwhitenoisesystemparameters.h"
#include "matrix.h"
#include "qtmatrix.h"
#include "standardwhitenoisesystemfactory.h"
#include "standardwhitenoisesystem.h"
#include "standardwhitenoisesystemparameters.h"
#include "trace.h"
#include "whitenoisesystemparametertype.h"
#include "kalmanfilterexperimentparameter.h"
#include "ui_qtwhitenoisesystemparametersdialog.h"
#include "qtkalmanfiltererparameterdialog.h"
#include "whitenoisesystemparameter.h"

QtWhiteNoiseSystemParametersDialog::QtWhiteNoiseSystemParametersDialog(
  const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtWhiteNoiseSystemParametersDialog),
    m_model(model)
{
  ui->setupUi(this);

  //Create the map
  {
    const std::vector<WhiteNoiseSystemParameterType> v = WhiteNoiseSystemParameter::GetAll();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(i < v.size());

      const WhiteNoiseSystemParameterType type = v[i];
      QtKalmanFiltererParameterDialog * const dialog
        = new QtKalmanFiltererParameterDialog(
          WhiteNoiseSystemParameter::ToName(type),
          WhiteNoiseSystemParameter::ToDescription(type),
          m_model->Find( KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(v[i]) )
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

  this->setFocusPolicy(Qt::NoFocus);
  ui->box_white_noise_system_type->setCurrentIndex(0);

  assert(m_model->CreateWhiteNoiseSystem() && "Obtain an empty white noise system (all components have size zero)");
}

QtWhiteNoiseSystemParametersDialog::~QtWhiteNoiseSystemParametersDialog()
{
  delete ui;
}

QtKalmanFiltererParameterDialog * QtWhiteNoiseSystemParametersDialog::Find(const WhiteNoiseSystemParameterType type)
{
    //Calls the const version of Find
    //To avoid duplication in const and non-const member functions
    // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines,
    //   and best practices. 2005. ISBN: 0-32-111358-6. Chapter 94: 'Avoid casting away const', item 'Exceptions'
    return const_cast<QtKalmanFiltererParameterDialog *>(const_cast<const QtWhiteNoiseSystemParametersDialog&>(*this).Find(type));
}

const QtKalmanFiltererParameterDialog * QtWhiteNoiseSystemParametersDialog::Find(const WhiteNoiseSystemParameterType type) const
{
  assert(m_parameters.find(type) != m_parameters.end());
  const QtKalmanFiltererParameterDialog * const table = (*m_parameters.find(type)).second;
  assert(table);
  return table;
}

int QtWhiteNoiseSystemParametersDialog::GetLag() const
{
  assert(ui->box_lag->value() >= 0);
  return ui->box_lag->value();
}

WhiteNoiseSystemType QtWhiteNoiseSystemParametersDialog::GetWhiteNoiseSystemType() const
{
  switch (ui->box_white_noise_system_type->currentIndex())
  {
    case 0: return WhiteNoiseSystemType::standard;
    case 1: return WhiteNoiseSystemType::lagged;
    default:
      assert(!"Unimplemented index of box_white_noise_system_type");
      throw std::logic_error(__func__);
  }
}

void QtWhiteNoiseSystemParametersDialog::on_box_white_noise_system_type_currentIndexChanged(int)
{
  //Notify the model
  m_model->SetWhiteNoiseSystemType(GetWhiteNoiseSystemType());

  switch (GetWhiteNoiseSystemType())
  {
    case WhiteNoiseSystemType::standard:
      ui->box_lag->setVisible(false);
      ui->label_lag->setVisible(false);
      break;
    case WhiteNoiseSystemType::lagged:
      ui->box_lag->setVisible(true);
      ui->label_lag->setVisible(true);
      break;
    case WhiteNoiseSystemType::n_types:
      assert(!"Unimplemented WhiteNoiseSystemType");
  }
}

void QtWhiteNoiseSystemParametersDialog::on_box_lag_valueChanged(int arg1)
{
  m_model->SetLagReal(arg1);
}
