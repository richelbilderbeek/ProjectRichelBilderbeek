#ifndef QTPVDBPRINTCONCEPTMAPDIALOG_H
#define QTPVDBPRINTCONCEPTMAPDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbPrintConceptMapDialog;
}

namespace ribi {

namespace pvdb {

///View the current work, optimized for humans
///This dialog will not be visible for humans at all in release
///QtPvdbPrintConceptMapDialog is optimized for printers
class QtPvdbPrintConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  explicit QtPvdbPrintConceptMapDialog(
    const boost::shared_ptr<pvdb::File>& file,
    QWidget *parent = 0);
  QtPvdbPrintConceptMapDialog(const QtPvdbPrintConceptMapDialog&) = delete;
  QtPvdbPrintConceptMapDialog& operator=(const QtPvdbPrintConceptMapDialog&) = delete;
  ~QtPvdbPrintConceptMapDialog() noexcept;
  void Print();

protected:
  void keyPressEvent(QKeyEvent * event);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();

private:
  Ui::QtPvdbPrintConceptMapDialog *ui;

  ///m_file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  const boost::shared_ptr<pvdb::File> m_file;

  QtPvdbConceptMapDisplayWidget * const m_widget;

  const std::vector<QWidget *> CollectWidgets() const;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBPRINTCONCEPTMAPDIALOG_H
