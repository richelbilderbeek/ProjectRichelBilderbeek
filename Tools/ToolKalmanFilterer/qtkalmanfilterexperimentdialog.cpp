#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtkalmanfilterexperimentdialog.h"

#include <cassert>
#include <cstdlib>
#include <fstream>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "kalmanfilter.h"
#include "kalmanfilterexample.h"
#include "kalmanfilterexperiment.h"
#include "kalmanfilterexperimentparameter.h"
#include "kalmanfilterparameter.h"
#include "kalmanfilterparameters.h"
#include "matrix.h"
#include "qtkalmanfilterdialog.h"
#include "qtkalmanfilterermodel.h"
#include "qtkalmanfilterexamplesdialog.h"
#include "qtmatrix.h"
#include "qtstandardkalmanfiltercalculationdialog.h"
#include "qtstdvectorstringmodel.h"
#include "qtsteadystatekalmanfiltercalculationdialog.h"
#include "qtwhitenoisesystemparametersdialog.h"
#include "standardwhitenoisesystemparameters.h"
#include "trace.h"
#include "ui_qtkalmanfilterexperimentdialog.h"

QtKalmanFilterExperimentDialog::QtKalmanFilterExperimentDialog(
  const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtKalmanFilterExperimentDialog),
    m_examples_dialog(new QtKalmanFilterExamplesDialog),
    m_filter_dialog(new QtKalmanFilterDialog(model)),
    m_model(model),
    m_noise_parameters_dialog(new QtWhiteNoiseSystemParametersDialog(model))
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  assert(m_examples_dialog);
  assert(m_filter_dialog);
  assert(m_model);
  assert(m_noise_parameters_dialog);
  assert(this->layout());
  //Create the map
  {
    const std::vector<KalmanFilterExperimentParameterType> v =
       KalmanFilterExperimentParameter::GetAll();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {

      assert(i < v.size());
      const KalmanFilterExperimentParameterType type = v[i];

      //Skip the KalmanFilterParameterType instances (these are done by KalmanFilterDialog
      if (KalmanFilterExperimentParameter::CanConvertToKalmanFilterParameter(type))
      {
        continue;
      }
      if (KalmanFilterExperimentParameter::CanConvertToWhiteNoiseSystemParameter(type))
      {
        continue;
      }

      QtKalmanFiltererParameterDialog * const dialog
        = new QtKalmanFiltererParameterDialog(
          KalmanFilterExperimentParameter::ToName(type),
          KalmanFilterExperimentParameter::ToDescription(type),
          m_model->Find(type)
        );
      assert(dialog);

      //Add to map
      m_parameters.insert(std::make_pair(type,dialog));

      //Add to dialog
      assert(this->layout());
      this->layout()->addWidget(dialog);

    }
    assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(KalmanFilterExperimentParameterType::n_parameters)
      && "All parameters must be in");
  }

  layout()->addWidget(new QLabel("Kalman filter parameters"));
  layout()->addWidget(m_filter_dialog);
  layout()->addWidget(new QLabel("White noise system parameters"));
  layout()->addWidget(m_noise_parameters_dialog);
  layout()->addWidget(new QLabel("Example settings"));
  layout()->addWidget(m_examples_dialog);

  assert(m_noise_parameters_dialog);
  assert(m_examples_dialog);

  //Connect clicking on the example buttons to setting (and showing) these
  QObject::connect(
    m_examples_dialog,SIGNAL(signal_example(boost::shared_ptr<KalmanFilterExample>)),
    this,SLOT(SetExample(boost::shared_ptr<KalmanFilterExample>)));

  //Make the white noise system parameters follow the possible tab changes in parameters
  QObject::connect(
    this->m_filter_dialog,SIGNAL(signal_kalman_filter_type_changed(KalmanFilterType)),
    this,SLOT(SetKalmanFilterType(KalmanFilterType)));

  ui->box_n_timesteps->setValue(5);
}

QtKalmanFilterExperimentDialog::~QtKalmanFilterExperimentDialog()
{
  delete ui;
  delete m_examples_dialog;
  delete m_filter_dialog;
  delete m_noise_parameters_dialog;
}

void QtKalmanFilterExperimentDialog::ClickExample(const int i)
{
  this->m_examples_dialog->ClickButton(i);
}


void QtKalmanFilterExperimentDialog::LoadFromDokuWiki(const std::string& filename)
{
  assert(QFile::exists(filename.c_str()));
  std::string text;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    text += s + "\n";
  }
  this->m_model->FromDokuWiki(text);
}

void QtKalmanFilterExperimentDialog::on_box_n_timesteps_valueChanged(int arg1)
{
  m_model->SetNumberOfTimesteps(arg1);
}


void QtKalmanFilterExperimentDialog::on_button_add_state_clicked()
{
  //Get the state names
  QAbstractTableModel * const abstract_model
    = m_model->Find(KalmanFilterExperimentParameterType::state_names);
  assert(abstract_model);
  StateNamesModel * const model = dynamic_cast<StateNamesModel*>(abstract_model);
  assert(model);
  std::vector<std::string> v = model->GetRawData();
  v.push_back(std::string("?"));
  model->SetRawData(v); //Set the data
  assert(model->GetRawData() == v);
}

void QtKalmanFilterExperimentDialog::on_button_remove_state_clicked()
{
  //Get the state names
  QAbstractTableModel * const abstract_model
    = m_model->Find(KalmanFilterExperimentParameterType::state_names);
  assert(abstract_model);
  StateNamesModel * const model = dynamic_cast<StateNamesModel*>(abstract_model);
  assert(model);
  std::vector<std::string> v = model->GetRawData();
  if (v.empty()) return;

  v.pop_back();
  model->SetRawData(v); //Set the data
  assert(model->GetRawData() == v);
}

void QtKalmanFilterExperimentDialog::on_button_load_clicked()
{
  if (ui->box_save->currentIndex() == 1)
  {
    QMessageBox b;
    b.setText("Loading from HTML not implemented");
    b.exec();
    return;
  }

  std::string filter;
  switch (ui->box_save->currentIndex())
  {
    case 0: //DokuWiki
      filter = "*.txt";
    break;
    case 1: //HTML
      filter = "*.htm";
    break;
    default:
      assert(!"Should not get here");
  }

  const QString filename = QFileDialog::getOpenFileName(
    0,
    "Please select a file to load the parameters from",
    "",
    filter.c_str());
  if (!filename.isEmpty())
  {
    switch (ui->box_save->currentIndex())
    {
      case 0: //DokuWiki
        this->LoadFromDokuWiki(filename.toStdString());
      break;
      case 1: //HTML
      {
        assert(!"Not implemented");
      }
      break;
      default:
        assert(!"Should not get here");
    }
  }
}

void QtKalmanFilterExperimentDialog::SaveToDokuWiki(const std::string& filename) const
{
  const std::string text = this->m_model->ToDokuWiki();
  std::ofstream f(filename.c_str());
  f << text;
}


void QtKalmanFilterExperimentDialog::on_button_save_clicked()
{
  std::string filter;
  switch (ui->box_save->currentIndex())
  {
    case 0: //DokuWiki
      filter = "*.txt";
    break;
    case 1: //HTML
      filter = "*.htm";
    break;
    default:
      assert(!"Should not get here");
  }

  const QString filename = QFileDialog::getSaveFileName(
    0,
    "Please select a file to save the parameters to",
    "",
    filter.c_str());
  if (!filename.isEmpty())
  {

    switch (ui->box_save->currentIndex())
    {
      case 0: //DokuWiki
      {
        SaveToDokuWiki(filename.toStdString());
      }
      break;
      case 1: //HTML
      {
        std::string text = this->m_model->ToHtml();
        std::ofstream f(filename.toStdString().c_str());
        f << text;
      }
      break;
      default:
        assert(!"Should not get here");
    }
  }
}

void QtKalmanFilterExperimentDialog::SetExample(const boost::shared_ptr<KalmanFilterExample> example)
{
  assert(example);
  assert(m_model);
  m_model->SetExample(example);
}

void QtKalmanFilterExperimentDialog::SetKalmanFilterType(const KalmanFilterType new_type)
{
  if (m_filter_dialog->GetKalmanFilterType() != new_type)
  {
    m_filter_dialog->SetKalmanFilterType(new_type);
  }
}

void QtKalmanFilterExperimentDialog::SetTimesteps(const int timesteps)
{
  assert(timesteps > 0);
  ui->box_n_timesteps->setValue(timesteps);
}

#ifndef NDEBUG
void QtKalmanFilterExperimentDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    TRACE("Starting QtKalmanFilterExperimentDialog::Test()")
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model(
      new QtKalmanFilterExperimentModel);
    const boost::shared_ptr<QtKalmanFilterExperimentDialog> d(
      new QtKalmanFilterExperimentDialog(model)
    );
    //Test DokuWiki conversion for discrete Kalman filter with empty parameters
    {
      d->SetTimesteps(2);
      d->SetKalmanFilterType(KalmanFilterType::standard);
      const std::string s = model->ToDokuWiki();
      model->SetNumberOfTimesteps(999999999);
      assert(s != model->ToDokuWiki());
      model->FromDokuWiki(s);
      assert(s == model->ToDokuWiki());
    }
    //Test DokuWiki conversion for steady state Kalman filter with empty parameters
    {
      d->SetTimesteps(2);
      d->SetKalmanFilterType(KalmanFilterType::steady_state);
      const std::string s = model->ToDokuWiki();
      model->SetNumberOfTimesteps(999999999);
      assert(s != model->ToDokuWiki());
      model->FromDokuWiki(s);
      assert(s == model->ToDokuWiki());
    }
    //Test read/write of examples
    const std::vector<boost::shared_ptr<KalmanFilterExample> > examples
      = KalmanFilterExample::CreateExamples();
    BOOST_FOREACH(const boost::shared_ptr<KalmanFilterExample>& example, examples)
    {
      model->SetExample(example);
      const std::string s = model->ToDokuWiki();
      model->SetNumberOfTimesteps(999999999);
      assert(s != model->ToDokuWiki());
      model->FromDokuWiki(s);
      assert(s == model->ToDokuWiki());
    }
    //Write all examples to file, and load these
    TRACE("Finished QtKalmanFilterExperimentDialog::Test()")
  }
}
#endif


