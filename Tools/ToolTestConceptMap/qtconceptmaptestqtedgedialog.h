#ifndef QTCONCEPTMAPTESTQTEDGEDIALOG_H
#define QTCONCEPTMAPTESTQTEDGEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapTestQtEdgeDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items when being a member of a cmap::QtNode,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtConceptMapTestQtEdgeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtConceptMapTestQtEdgeDialog(QWidget *parent = 0);
  QtConceptMapTestQtEdgeDialog(const QtConceptMapTestQtEdgeDialog&) = delete;
  QtConceptMapTestQtEdgeDialog& operator=(const QtConceptMapTestQtEdgeDialog&) = delete;
  ~QtConceptMapTestQtEdgeDialog() noexcept;
  int GetTestIndex() const noexcept;
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

  void on_button_load_test_clicked();

private:

  Ui::QtConceptMapTestQtEdgeDialog *ui;
  boost::shared_ptr<Edge> m_edge;
  cmap::QtEdge* m_edge_item;
  const boost::shared_ptr<Node> m_from;
  const boost::shared_ptr<Node> m_to;

  static const boost::shared_ptr<Node> CreateFrom();
  static const boost::shared_ptr<Node> CreateTo();

  ///Get the Edge via the route chosen by box_edit
  boost::shared_ptr<Edge> GetEdgeCurrentWay();

  ///Get the Edge from a route
  boost::shared_ptr<Edge> GetEdge(const int index);

  void SetEdge(const boost::shared_ptr<Edge>& edge) noexcept;

  ///Called whenever an item requests a scene update
  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTQTEDGEDIALOG_H

