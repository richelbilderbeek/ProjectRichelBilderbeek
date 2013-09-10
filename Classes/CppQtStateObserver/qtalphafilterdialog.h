#ifndef QTALPHAFILTERDIALOG_H
#define QTALPHAFILTERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#include "stateobserverfwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtAlphaFilterDialog;
}

namespace ribi {

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

} //~namespace ribi

#endif // QTALPHAFILTERDIALOG_H
