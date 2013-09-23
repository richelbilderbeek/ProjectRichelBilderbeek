#ifndef QTPVDBPRINTRATINGDIALOG_H
#define QTPVDBPRINTRATINGDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "pvdbfwd.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbPrintRatingDialog;
}

struct QTableWidget;

namespace ribi {

namespace pvdb {

///View the current rating, optimized for printers
///This dialog will not be visible for humans at all in release
///QtPvdbRatingDialog is optimized for humans
class QtPvdbPrintRatingDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///file be const, as the Display Concept map cannot deal with const ribi::pvdb::ConceptMap (yet?)
  explicit QtPvdbPrintRatingDialog(
    const boost::shared_ptr<pvdb::File>& file,
    QWidget *parent = 0);
  QtPvdbPrintRatingDialog(const QtPvdbPrintRatingDialog&) = delete;
  QtPvdbPrintRatingDialog& operator=(const QtPvdbPrintRatingDialog&) = delete;
  ~QtPvdbPrintRatingDialog() noexcept;

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

  ///m_file be const, as the Display Concept map cannot deal with const ribi::pvdb::ConceptMap (yet?)
  const boost::shared_ptr<pvdb::File> m_file;

  QtPvdbConceptMapRateWidget * const m_widget;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBPRINTRATINGDIALOG_H
