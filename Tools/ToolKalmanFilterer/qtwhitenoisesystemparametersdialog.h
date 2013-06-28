#ifndef QTWHITENOISESYSTEMPARAMETERSDIALOG
#define QTWHITENOISESYSTEMPARAMETERSDIALOG

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <map>
#include <vector>

#include <QDialog>
#include <QTableWidget>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include "laggedwhitenoisesystemparameters.h"
#include "qtkalmanfiltererparameterdialog.h"
#include "qtkalmanfilterexperimentmodel.h"
#include "standardwhitenoisesystemparameters.h"
#include "whitenoisesystem.h"
#include "whitenoisesystemparametertype.h"
#include "whitenoisesystemtype.h"

namespace Ui {
  class QtWhiteNoiseSystemParametersDialog;
}

class QtWhiteNoiseSystemParametersDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtWhiteNoiseSystemParametersDialog(
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
    QWidget *parent = 0);
  ~QtWhiteNoiseSystemParametersDialog();

  ///Read the lag (in timesteps) from the dialog
  int GetLag() const;

  #ifndef NDEBUG
  ///Obtain the GUI
  Ui::QtWhiteNoiseSystemParametersDialog * GetUi() { return ui; }

  bool IsValid() const;
  #endif

  ///Obtain the white noise system type
  WhiteNoiseSystemType GetWhiteNoiseSystemType() const;

  ///Set the white noise system type
  void SetWhiteNoiseSystemType(const WhiteNoiseSystemType type);

private:
  Ui::QtWhiteNoiseSystemParametersDialog *ui;

  ///The model
  const boost::shared_ptr<QtKalmanFilterExperimentModel> m_model;

  ///The parameter type and its corresponding dialog
  std::map<WhiteNoiseSystemParameterType,QtKalmanFiltererParameterDialog *> m_parameters;

private slots:

  ///Find a WhiteNoiseSystemParameterType its corresponding table
  QtKalmanFiltererParameterDialog * Find(const WhiteNoiseSystemParameterType type);
  const QtKalmanFiltererParameterDialog * Find(const WhiteNoiseSystemParameterType type) const;


  void on_box_white_noise_system_type_currentIndexChanged(int index);

  void on_box_lag_valueChanged(int arg1);

  #ifndef NDEBUG
  static void Test();
  #endif
};

#endif // QTWHITENOISESYSTEMPARAMETERSDIALOG
