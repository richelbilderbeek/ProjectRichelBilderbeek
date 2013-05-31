#ifndef QTKALMANFILTERERPARAMETERDIALOG
#define QTKALMANFILTERERPARAMETERDIALOG

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>

#include <QDialog>
#include <QTableWidgetItem>

//#include <boost/shared_ptr.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/vector.hpp>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
//#include "kalmanfilterparametertype.h"
//#include "kalmanfilterexperimentparametertype.h"
//#include "whitenoisesystemparametertype.h"

namespace Ui {
  class QtKalmanFiltererParameterDialog;
}

///Dialog for a parameter, stores a QtKalmanFiltererParameterDialog::ValueType
class QtKalmanFiltererParameterDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFiltererParameterDialog(
    const std::string& parameter_name,
    const std::string& parameter_description,
    QAbstractTableModel * const model,
    QWidget *parent = 0);

  ~QtKalmanFiltererParameterDialog();

  ///Convert the table and its content to HTML
  const std::string ToHtml() const;

signals:
  ///Emitted when table changes from/to a valid to/from an invalid state
  void signal_state_changed();

private:
  Ui::QtKalmanFiltererParameterDialog *ui;

private slots:

};

#endif // QTKALMANFILTERERPARAMETERDIALOG
