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
#include "kalmanfiltertypes.h"
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
#include "ui_qtwhitenoisesystemparametersdialog.h"
#include "whitenoisesystemparameter.h"
#include "whitenoisesystemtypes.h"

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
    m_examples_dialog,SIGNAL(signal_example(KalmanFilterExample*const)),
    this,SLOT(SetExample(KalmanFilterExample*const)));

  //Make the white noise system parameters follow the possible tab changes in parameters
  QObject::connect(
    this->m_filter_dialog,SIGNAL(signal_kalman_filter_type_changed(KalmanFilterType)),
    this,SLOT(SetKalmanFilterType(KalmanFilterType)));

  ui->box_n_timesteps->setValue(5);

  assert(IsValid());
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
  m_signal_new_parameters();
  assert(IsValid());
}

int QtKalmanFilterExperimentDialog::GetNumberOfTimesteps() const
{
  return ui->box_n_timesteps->value();
}

#ifndef NDEBUG
bool QtKalmanFilterExperimentDialog::IsValid() const
{
  if (this->GetNumberOfTimesteps() != m_model->GetNumberOfTimesteps())
  {
    TRACE("Different number of timesteps");
    return false;
  }
  if (GetNoiseParametersDialog()->GetWhiteNoiseSystemType()
    != m_model->CreateWhiteNoiseSystemParameters()->GetType())
  {
    TRACE("Different white noise system type");
    return false;
  }
  if (GetFilterDialog()->GetKalmanFilterType()
    != m_model->CreateKalmanFilter()->GetType())
  {
    TRACE("Different Kalman Filter types");
    TRACE(KalmanFilterTypes::ToStr(GetFilterDialog()->GetKalmanFilterType()));
    TRACE(KalmanFilterTypes::ToStr(m_model->CreateKalmanFilter()->GetType()));
    return false;
  }
  return true;
}
#endif

void QtKalmanFilterExperimentDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;

  if (event->modifiers() == Qt::AltModifier)
  {
    const int index = event->key() - '0';
    const int max_index = boost::numeric_cast<int>(KalmanFilterExample::CreateExamples().size());
    if (index < max_index)
    {
      ClickExample(index);
      m_signal_new_parameters();
      return;
    }
  }

  QDialog::keyPressEvent(event);
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

  this->SetNumberOfTimesteps(m_model->GetNumberOfTimesteps());

  assert(IsValid());
}

void QtKalmanFilterExperimentDialog::on_box_n_timesteps_valueChanged(int arg1)
{
  m_model->SetNumberOfTimesteps(arg1);
  assert(m_model->GetNumberOfTimesteps() == this->GetNumberOfTimesteps());
  //Don't check here: this value might be set in a sequence of
  // SetNumberOfTimesteps - SetKalmanFilterType - SetWhiteNoiseSystemType
  //Everywhere in between this sequence, this dialog is in an invalid state
  //assert(IsValid());
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
  assert(IsValid());
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
  assert(IsValid());
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

  assert(IsValid());
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

void QtKalmanFilterExperimentDialog::SetExample(const KalmanFilterExample * const example_raw)
{
  assert(example_raw);
  const boost::shared_ptr<const KalmanFilterExample> example(example_raw);
  assert(example);
  assert(m_model);

  m_model->SetExample(example);

  #ifndef NDEBUG
  const boost::shared_ptr<KalmanFilterExperiment> experiment = m_model->CreateExperiment();
  assert(experiment);
  assert(experiment->GetKalmanFilter());
  assert(experiment->GetStateNames() == example->GetStateNames());
  assert(experiment->GetKalmanFilter()->GetParameters()->GetType() == example->GetKalmanFilterParameters()->GetType());
  if (const boost::shared_ptr<const StandardKalmanFilterParameters> p_experiment = boost::dynamic_pointer_cast<const StandardKalmanFilterParameters>(experiment->GetKalmanFilter()->GetParameters()))
  {
    assert(p_experiment);
    const boost::shared_ptr<const StandardKalmanFilterParameters> p_example
      = boost::dynamic_pointer_cast<const StandardKalmanFilterParameters>(example->GetKalmanFilterParameters());
    assert(p_example);
    assert(Matrix::MatricesAreEqual( p_experiment->GetControl(), p_example->GetControl() ) );
    assert(StandardKalmanFilterParameters::IsAboutEqual(*p_experiment,*p_example));
  }
  #endif
  assert(IsValid());
}

void QtKalmanFilterExperimentDialog::SetKalmanFilterType(const KalmanFilterType new_type)
{
  if (m_filter_dialog->GetKalmanFilterType() != new_type)
  {
    m_filter_dialog->SetKalmanFilterType(new_type);
    assert(m_filter_dialog->GetKalmanFilterType() == new_type);
  }
  assert(m_filter_dialog->GetKalmanFilterType() == new_type);
  assert(m_model->CreateKalmanFilterParameters()->GetType() == new_type);

  //Don't check here: this value might be set in a sequence of
  // SetNumberOfTimesteps - SetKalmanFilterType - SetWhiteNoiseSystemType
  //Everywhere in between this sequence, this dialog is in an invalid state
  //assert(IsValid());
}

void QtKalmanFilterExperimentDialog::SetNumberOfTimesteps(const int timesteps)
{
  assert(timesteps > 0);
  ui->box_n_timesteps->setValue(timesteps);
  assert(GetNumberOfTimesteps() == timesteps);
  assert(m_model->GetNumberOfTimesteps() == timesteps);

  //Don't check here: this value might be set in a sequence of
  // SetNumberOfTimesteps - SetKalmanFilterType - SetWhiteNoiseSystemType
  //Everywhere in between this sequence, this dialog is in an invalid state
  //assert(IsValid());
}

#ifndef NDEBUG
void QtKalmanFilterExperimentDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtKalmanFilterExperimentDialog::Test()")
  //TRACE("Test QtWhiteNoiseSystemParametersDialog");
  {
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model(
      new QtKalmanFilterExperimentModel);
    QtWhiteNoiseSystemParametersDialog d(model);
  }
  //TRACE("Test QtKalmanFilterExperimentModel");
  {
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model(
      new QtKalmanFilterExperimentModel);
    const boost::shared_ptr<QtKalmanFilterExperimentDialog> d(
      new QtKalmanFilterExperimentDialog(model)
    );
    //TRACE("Test DokuWiki conversion for all Kalman filter types with empty parameters")
    const std::vector<KalmanFilterType> kalman_filter_types = KalmanFilterTypes::GetAllTypes();
    const std::size_t n_kalman_filter_types = kalman_filter_types.size();
    for (std::size_t i=0; i!=n_kalman_filter_types; ++i)
    {
      const KalmanFilterType kalman_filter_type = kalman_filter_types[i];
      if (kalman_filter_type == KalmanFilterType::fixed_lag_smoother)
      {
        TRACE("Fixed lag smoother not supported yet");
        continue;
      }

      d->SetNumberOfTimesteps(2);
      d->SetKalmanFilterType(kalman_filter_type);
      const std::string s = model->ToDokuWiki();
      assert(s == model->ToDokuWiki());
      model->SetNumberOfTimesteps(3);
      assert(s != model->ToDokuWiki());
      model->FromDokuWiki(s);
      assert(s == model->ToDokuWiki());


      const std::vector<WhiteNoiseSystemType> white_noise_system_types = WhiteNoiseSystemTypes::GetAllTypes();
      const std::size_t n_white_noise_system_types = white_noise_system_types.size();
      for (std::size_t j=0; j!=n_white_noise_system_types; ++j)
      {
        const WhiteNoiseSystemType white_noise_system_type = white_noise_system_types[j];
        d->SetNumberOfTimesteps(4);
        d->SetKalmanFilterType(kalman_filter_type);
        d->GetNoiseParametersDialog()->SetWhiteNoiseSystemType(white_noise_system_type);
        const std::string s = model->ToDokuWiki();
        assert(s == model->ToDokuWiki());
        model->SetNumberOfTimesteps(5);
        assert(s != model->ToDokuWiki());
        model->FromDokuWiki(s);
        assert(s == model->ToDokuWiki());
      }
    }
    //TRACE("Test backwards compatibility in reading/writing DokuWiki")
    {
      QFile file(":/files/0.txt");
      assert(file.size() > 0);
      const std::string temp_filename = "tmp_0.txt";
      file.copy(temp_filename.c_str());
      assert(QFile::exists(temp_filename.c_str()));

      d->LoadFromDokuWiki(temp_filename);
    }
    //TRACE("Test read/write of examples");
    const std::vector<boost::shared_ptr<KalmanFilterExample> > examples
      = KalmanFilterExample::CreateExamples();
    int cnt = 1;
    BOOST_FOREACH(const boost::shared_ptr<KalmanFilterExample>& example, examples)
    {
      assert(model);
      assert(example);
      model->SetExample(example);
      d->SaveToDokuWiki(boost::lexical_cast<std::string>(cnt) + std::string(".txt"));
      ++cnt;
      const std::string s = model->ToDokuWiki();
      model->SetNumberOfTimesteps(999999999);
      assert(s != model->ToDokuWiki());
      model->FromDokuWiki(s);
      assert(s == model->ToDokuWiki());
    }
    //TRACE("Test all white noise system types")
    {
      const int sz = d->m_noise_parameters_dialog->GetUi()->box_white_noise_system_type->count();
      assert(sz > 0);
      assert(sz == static_cast<int>(WhiteNoiseSystemType::n_types));
      for (int i=0; i!=sz; ++i)
      {
        d->m_noise_parameters_dialog->GetUi()->box_white_noise_system_type->setCurrentIndex(i);
        assert(model->CreateWhiteNoiseSystemParameters());
      }
    }
  }
  TRACE("Finished QtKalmanFilterExperimentDialog::Test()")
}
#endif


