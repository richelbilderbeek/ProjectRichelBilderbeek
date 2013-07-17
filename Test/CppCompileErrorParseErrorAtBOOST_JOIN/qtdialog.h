#ifndef QTDIALOG_H
#define QTDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <QDialog>

#include <boost/algorithm/string/split.hpp>
//#include <boost/algorithm/string/trim.hpp>
//#include <boost/bind.hpp>
#include <boost/foreach.hpp>
//#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/numeric/conversion/cast.hpp>
//#include <boost/numeric/ublas/functional.hpp>
//#include <boost/numeric/ublas/functional.hpp>
//#include <boost/numeric/ublas/functional.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/vector.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/signals2.hpp>


#include <boost/algorithm/string/split.hpp>
//#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif


namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private:
  Ui::QtDialog *ui;
};

#endif // QTDIALOG_H
