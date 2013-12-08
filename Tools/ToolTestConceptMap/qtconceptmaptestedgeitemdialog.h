#ifndef QTCONCEPTMAPTESTEDGEITEMDIALOG_H
#define QTCONCEPTMAPTESTEDGEITEMDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapTestEdgeItemDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items when being a member of a cmap::QtNode,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtConceptMapTestEdgeItemDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtConceptMapTestEdgeItemDialog(QWidget *parent = 0);
  QtConceptMapTestEdgeItemDialog(const QtConceptMapTestEdgeItemDialog&) = delete;
  QtConceptMapTestEdgeItemDialog& operator=(const QtConceptMapTestEdgeItemDialog&) = delete;
  ~QtConceptMapTestEdgeItemDialog() noexcept;
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

  Ui::QtConceptMapTestEdgeItemDialog *ui;
  boost::shared_ptr<ribi::cmap::Edge> m_edge;
  cmap::QtEdge* m_edge_item;
  const boost::shared_ptr<ribi::cmap::Node> m_from;
  const boost::shared_ptr<ribi::cmap::Node> m_to;

  static const boost::shared_ptr<ribi::cmap::Node> CreateFrom();
  static const boost::shared_ptr<ribi::cmap::Node> CreateTo();

  ///Get the Edge via the route chosen by box_edit
  const boost::shared_ptr<ribi::cmap::Edge> GetEdgeCurrentWay();

  ///Get the Edge from a route
  const boost::shared_ptr<ribi::cmap::Edge> GetEdge(const int index);

  ///Called whenever an item requests a scene update
  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDGEITEMDIALOG_H

