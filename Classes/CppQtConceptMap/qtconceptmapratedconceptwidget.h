#ifndef QTPVDBRATEDCONCEPTWIDGET_H
#define QTPVDBRATEDCONCEPTWIDGET_H


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

namespace Ui {
  class QtConceptMapRatedConceptWidget;
}

namespace ribi {
namespace cmap {

class QtConceptMapRatedConceptWidget : public QDialog
{
  Q_OBJECT
  
public:

  explicit QtConceptMapRatedConceptWidget(
    const boost::shared_ptr<const ribi::cmap::ConceptMap> concept_map,
    const boost::shared_ptr<const cmap::Node> node,
    QWidget *parent = 0);
  QtConceptMapRatedConceptWidget(const QtConceptMapRatedConceptWidget&) = delete;
  QtConceptMapRatedConceptWidget& operator=(const QtConceptMapRatedConceptWidget&) = delete;
  ~QtConceptMapRatedConceptWidget();

  ///Hides the rating. This is used when a student views his/her
  ///work before an assessor has rated his/her work
  void HideRating();

private slots:
  void DoResizeLists();

private:
  Ui::QtConceptMapRatedConceptWidget *ui;
  QTimer * const m_timer;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBRATEDCONCEPTWIDGET_H
