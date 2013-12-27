#ifndef QTCONCEPTMAPRATEDCONCEPTDIALOG_H
#define QTCONCEPTMAPRATEDCONCEPTDIALOG_H


#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapRatedConceptDialog; }

namespace ribi {
namespace cmap {

class QtConceptMapRatedConceptDialog : public QDialog
{
  Q_OBJECT
  
public:

  explicit QtConceptMapRatedConceptDialog(
    const boost::shared_ptr<const ribi::cmap::ConceptMap> concept_map,
    const boost::shared_ptr<const cmap::Node> node,
    QWidget *parent = 0);
  QtConceptMapRatedConceptDialog(const QtConceptMapRatedConceptDialog&) = delete;
  QtConceptMapRatedConceptDialog& operator=(const QtConceptMapRatedConceptDialog&) = delete;
  ~QtConceptMapRatedConceptDialog();

  ///Hides the rating. This is used when a student views his/her
  ///work before an assessor has rated his/her work
  void HideRating();

private slots:
  void DoResizeLists();

private:
  Ui::QtConceptMapRatedConceptDialog *ui;
  QTimer * const m_timer;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTCONCEPTMAPRATEDCONCEPTDIALOG_H
