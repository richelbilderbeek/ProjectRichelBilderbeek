#ifndef QTPVDBTESTEDGEITEMDIALOG_H
#define QTPVDBTESTEDGEITEMDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbTestEdgeItemDialog; }

namespace ribi {

namespace pvdb {

///Tests all QtPvdbConceptItem items when being a member of a QtPvdbNodeItem,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestEdgeItemDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestEdgeItemDialog(QWidget *parent = 0);
  QtPvdbTestEdgeItemDialog(const QtPvdbTestEdgeItemDialog&) = delete;
  QtPvdbTestEdgeItemDialog& operator=(const QtPvdbTestEdgeItemDialog&) = delete;
  ~QtPvdbTestEdgeItemDialog();
protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_box_competency_currentIndexChanged(int index);
  void on_edit_name_textChanged(const QString &arg1);
  void on_box_complexity_currentIndexChanged(const QString &arg1);
  void on_box_concreteness_currentIndexChanged(const QString &arg1);
  void on_box_specificity_currentIndexChanged(const QString &arg1);
  void on_edit_example_text_textChanged(const QString &arg1);

  void on_box_arrow_head_currentIndexChanged(int index);

  void on_box_arrow_tail_currentIndexChanged(int index);

private:

  Ui::QtPvdbTestEdgeItemDialog *ui;
  boost::shared_ptr<ribi::pvdb::Edge> m_edge;
  QtPvdbEdgeItem* m_edge_item;
  const boost::shared_ptr<ribi::pvdb::Node> m_from;
  const boost::shared_ptr<ribi::pvdb::Node> m_to;

  static const boost::shared_ptr<ribi::pvdb::Node> CreateFrom();
  static const boost::shared_ptr<ribi::pvdb::Node> CreateTo();

  ///Get the Edge via the route chosen by box_edit
  const boost::shared_ptr<ribi::pvdb::Edge> GetEdgeCurrentWay();

  ///Get the Edge from a route
  const boost::shared_ptr<ribi::pvdb::Edge> GetEdge(const int index);

  ///Called whenever an item requests a scene update
  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBTESTEDGEITEMDIALOG_H

