#ifndef QTPVDBCONCEPTEDITDIALOG_H
#define QTPVDBCONCEPTEDITDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"


struct QListWidgetItem;

namespace Ui {
class QtPvdbConceptEditDialog;
}

namespace ribi {
namespace pvdb {

class QtPvdbConceptEditDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///concept is not const as user might want to modify it
  ///concept is only modified if user clicks OK
  explicit QtPvdbConceptEditDialog(
    const boost::shared_ptr<ribi::pvdb::Concept> concept,
    QWidget* parent = 0);
  QtPvdbConceptEditDialog(const QtPvdbConceptEditDialog&) = delete;
  QtPvdbConceptEditDialog& operator=(const QtPvdbConceptEditDialog&) = delete;
  ~QtPvdbConceptEditDialog();

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void RemoveEmptyItem(QListWidgetItem * item);

  void on_button_add_clicked();

  ///Finally convert what the GUI displays to a Concept
  void on_button_ok_clicked();

private:
  Ui::QtPvdbConceptEditDialog *ui;


#ifdef PVDB_WRITE_TO_CONCEPT
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specificity;
#else
  ///The concept being modified, cannot be const
  const boost::shared_ptr<ribi::pvdb::Concept> m_concept;

#endif

  ///Test this class
  static void Test();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCONCEPTEDITDIALOG_H
