#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtkalmanfiltererparameterdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QTableWidgetItem>

#include "fixedlagsmootherkalmanfilter.h"
#include "kalmanfilterexperimentparameter.h"
#include "kalmanfilterparameter.h"
#include "kalmanfilterparametertype.h"
#include "matrix.h"
#include "qtmatrix.h"
#include "kalmanfilterexperimentparameter.h"
#include "whitenoisesystemparameter.h"
#include "qtkalmanfilterermodel.h"
#include "qtublasmatrixdoublemodel.h"
#include "qtublasvectordoublemodel.h"
#include "qtstdvectorfunctionmodel.h"

#include "qtstdvectorstringmodel.h"
#include "standardkalmanfilter.h"
#include "standardkalmanfilterfactory.h"
#include "steadystatekalmanfilter.h"
#include "qtkalmanfilterexperimentdialog.h"
#include "steadystatekalmanfilterfactory.h"
#include "trace.h"
#include "ui_qtkalmanfiltererparameterdialog.h"

QtKalmanFiltererParameterDialog::QtKalmanFiltererParameterDialog(
  const std::string& parameter_name,
  const std::string& parameter_description,
  QAbstractTableModel * const model,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtKalmanFiltererParameterDialog)
{
  

  ui->setupUi(this);
  this->setFocusPolicy(Qt::NoFocus);
  
  ui->table->setModel(model);
  ui->label->setText(parameter_name.c_str());
  this->setToolTip(parameter_description.c_str());

  ui->table->setAlternatingRowColors(true);
  ui->table->setWordWrap(false);
}

QtKalmanFiltererParameterDialog::~QtKalmanFiltererParameterDialog()
{
  delete ui;
}

const std::string QtKalmanFiltererParameterDialog::ToHtml() const
{
  std::string s;
  s+="<table summary=\"" + ui->label->text().toStdString() + "\" border=\"1\">";
  const int n_cols = ui->table->model()->columnCount();
  const int n_rows = ui->table->model()->rowCount();
  for (int row = 0; row!=n_rows; ++row)
  {
    s +="<tr>";
    for (int col = 0; col!=n_cols; ++col)
    {
      s +="<td>";
      const QModelIndex index = ui->table->model()->index(row,col);
      const QString q = ui->table->model()->data(index).toString();
      s += q.toStdString();
      s +="</td>";
    }
    s +="</tr>";
  }
  s += "</table>";
  return s;
}

