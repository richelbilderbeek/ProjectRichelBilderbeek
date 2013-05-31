#ifndef QTPVDBPRINTCONCEPTMAPDIALOG_H
#define QTPVDBPRINTCONCEPTMAPDIALOG_H

#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
#include "qthideandshowdialog.h"

namespace Ui {
  class QtPvdbPrintConceptMapDialog;
}

class QtPvdbPrintConceptMapDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbPrintConceptMapDialog(
    const boost::shared_ptr<const pvdb::File>& file,
    QWidget *parent = 0);
  ~QtPvdbPrintConceptMapDialog();
  
protected:
  void keyPressEvent(QKeyEvent * event);

private slots:
  void on_button_print_clicked();

private:
  Ui::QtPvdbPrintConceptMapDialog *ui;
};

#endif // QTPVDBPRINTCONCEPTMAPDIALOG_H
