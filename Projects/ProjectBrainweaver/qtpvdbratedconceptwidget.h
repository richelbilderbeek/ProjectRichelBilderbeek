#ifndef QTPVDBRATEDCONCEPTWIDGET_H
#define QTPVDBRATEDCONCEPTWIDGET_H


#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <QDialog>
#include "pvdbfwd.h"

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
  ~QtPvdbRatedConceptWidget();

  ///Hides the rating. This is used when a student views his/her
  ///work before an assessor has rated his/her work
  void HideRating();
  
private:
  Ui::QtPvdbRatedConceptWidget *ui;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBRATEDCONCEPTWIDGET_H
