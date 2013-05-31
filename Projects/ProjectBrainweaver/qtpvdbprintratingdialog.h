#ifndef QTPVDBPRINTRATINGDIALOG_H
#define QTPVDBPRINTRATINGDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "pvdbfwd.h"
#include "qthideandshowdialog.h"

namespace Ui {
  class QtPvdbPrintRatingDialog;
}

struct QTableWidget;

///View the current rating, optimized for printers
///This dialog will not be visible for humans at all in release
///QtPvdbRatingDialog is optimized for humans
class QtPvdbPrintRatingDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///file be const, as the Display Concept map cannot deal with const pvdb::ConceptMap (yet?)
  explicit QtPvdbPrintRatingDialog(
    const boost::shared_ptr<pvdb::File>& file,
    QWidget *parent = 0);
  ~QtPvdbPrintRatingDialog();

  QTableWidget * GetTableConcepts();
  QTableWidget * GetTableExamples();
  QTableWidget * GetTableValues();
  void Print();

protected:
  void keyPressEvent(QKeyEvent * event);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();
  const std::vector<QWidget *> CollectWidgets() const;
private:
  Ui::QtPvdbPrintRatingDialog *ui;

  ///m_file be const, as the Display Concept map cannot deal with const pvdb::ConceptMap (yet?)
  const boost::shared_ptr<pvdb::File> m_file;
};

#endif // QTPVDBPRINTRATINGDIALOG_H
