#ifndef QTALPHAFILTERDIALOG_H
#define QTALPHAFILTERDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include <QDialog>
#include "stateobserverfwd.h"

namespace Ui {
  class QtAlphaFilterDialog;
}

///Dialog to create an alpha filter
class QtAlphaFilterDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtAlphaFilterDialog(QWidget *parent = 0);
  ~QtAlphaFilterDialog();

  ///Create an alpha filter with the current parameters
  boost::shared_ptr<AlphaFilter> Create() const;

  
private:
  Ui::QtAlphaFilterDialog *ui;
};

#endif // QTALPHAFILTERDIALOG_H
