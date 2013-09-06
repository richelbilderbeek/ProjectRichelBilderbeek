#ifndef QTPVDBTESTCONCEPTITEMDIALOG_H
#define QTPVDBTESTCONCEPTITEMDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbTestConceptItemDialog; }

namespace ribi {

namespace pvdb {

///Tests all QtPvdbConceptItem items, especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestConceptItemDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestConceptItemDialog(QWidget *parent = 0);
  ~QtPvdbTestConceptItemDialog();

protected:
  void keyPressEvent(QKeyEvent *event);
  
private slots:

  void on_box_competency_currentIndexChanged(int index);
  void on_edit_name_textChanged(const QString &arg1);
  void on_box_complexity_currentIndexChanged(const QString &arg1);
  void on_box_concreteness_currentIndexChanged(const QString &arg1);
  void on_box_specificity_currentIndexChanged(const QString &arg1);
  void on_edit_example_text_textChanged(const QString &arg1);

private:
  Ui::QtPvdbTestConceptItemDialog *ui;
  const boost::shared_ptr<ribi::pvdb::Concept> m_concept;
  QtPvdbDisplayConceptItem* m_display_concept;
  QtPvdbEditConceptItem* m_edit_concept;
  QtPvdbRateConceptItem* m_rate_concept;

  ///Get the Concept via the route chosen by box_edit
  const boost::shared_ptr<ribi::pvdb::Concept> GetChosenConcept();

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBTESTCONCEPTITEMDIALOG_H
