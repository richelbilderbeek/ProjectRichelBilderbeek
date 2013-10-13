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
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbRatedConceptWidget;
}

namespace ribi {
namespace pvdb {

class QtPvdbRatedConceptWidget : public QDialog
{
  Q_OBJECT
  
public:

  explicit QtPvdbRatedConceptWidget(
    const boost::shared_ptr<const ribi::pvdb::ConceptMap> concept_map,
    const boost::shared_ptr<const pvdb::Node> node,
    QWidget *parent = 0);
  QtPvdbRatedConceptWidget(const QtPvdbRatedConceptWidget&) = delete;
  QtPvdbRatedConceptWidget& operator=(const QtPvdbRatedConceptWidget&) = delete;
  ~QtPvdbRatedConceptWidget();

  ///Hides the rating. This is used when a student views his/her
  ///work before an assessor has rated his/her work
  void HideRating();

private slots:
  void DoResizeLists();

private:
  Ui::QtPvdbRatedConceptWidget *ui;
  QTimer * const m_timer;

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBRATEDCONCEPTWIDGET_H
