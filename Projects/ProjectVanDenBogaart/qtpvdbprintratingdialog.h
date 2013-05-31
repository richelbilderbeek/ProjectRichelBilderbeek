#ifndef QTPVDBPRINTRATINGDIALOG_H
#define QTPVDBPRINTRATINGDIALOG_H

#include <boost/shared_ptr.hpp>
#include "pvdbfwd.h"
#include "qthideandshowdialog.h"

namespace Ui {
  class QtPvdbPrintRatingDialog;
}

struct QTableWidget;

class QtPvdbPrintRatingDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbPrintRatingDialog(
    const boost::shared_ptr<const pvdb::File>& file,
    QWidget *parent = 0);
  ~QtPvdbPrintRatingDialog();

  QTableWidget * GetTableConcepts();
  QTableWidget * GetTableExamples();
  QTableWidget * GetTableValues();

protected:
  void keyPressEvent(QKeyEvent * event);

private slots:
  void on_button_print_clicked();

private:
  Ui::QtPvdbPrintRatingDialog *ui;
};

#endif // QTPVDBPRINTRATINGDIALOG_H
