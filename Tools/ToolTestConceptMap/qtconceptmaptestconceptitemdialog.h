#ifndef QTCONCEPTMAPTESTCONCEPTITEMDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTITEMDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapTestConceptItemDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items, especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtConceptMapTestConceptItemDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtConceptMapTestConceptItemDialog(QWidget *parent = 0);
  QtConceptMapTestConceptItemDialog(const QtConceptMapTestConceptItemDialog&) = delete;
  QtConceptMapTestConceptItemDialog& operator=(const QtConceptMapTestConceptItemDialog&) = delete;
  ~QtConceptMapTestConceptItemDialog() noexcept;

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
  Ui::QtConceptMapTestConceptItemDialog *ui;
  const boost::shared_ptr<Concept> m_concept;
  cmap::QtDisplayStrategy* m_display_concept;
  cmap::QtEditStrategy* m_edit_concept;
  cmap::QtRateStrategy* m_rate_concept;

  ///Get the Concept via the route chosen by box_edit
  const boost::shared_ptr<Concept> GetChosenConcept();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTITEMDIALOG_H
