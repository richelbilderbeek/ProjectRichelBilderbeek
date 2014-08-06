#ifndef QTCONCEPTMAPQTEDGEDIALOG_H
#define QTCONCEPTMAPQTEDGEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop


namespace Ui {
  class QtQtEdgeDialog;
}

namespace ribi {
namespace cmap {

class QtQtEdgeDialog : public ::ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtQtEdgeDialog(QWidget *parent = 0);
  QtQtEdgeDialog(const QtQtEdgeDialog&) = delete;
  QtQtEdgeDialog& operator=(const QtQtEdgeDialog&) = delete;
  ~QtQtEdgeDialog();


  static int GetMinimumHeight(const QtEdge& qtedge) noexcept;
  boost::shared_ptr<QtEdge> GetQtEdge() const noexcept { return m_qtedge; }
  //Obtain the X coordinat of the Node on the Edge from the GUI
  double GetUiX() const noexcept;
  //Obtain the Y coordinat of the Node on the Edge from the GUI
  double GetUiY() const noexcept;

  void SetQtEdge(const boost::shared_ptr<QtEdge>& qtedge) noexcept;
  //Set the X coordinat of the Node on the Edge via the GUI
  void SetUiX(const double x) const noexcept;
  //Set the Y coordinat of the Node on the Edge via the GUI
  void SetUiY(const double y) const noexcept;

private:
  Ui::QtQtEdgeDialog *ui;

  ///The QtEdge to work on
  ///A QtEdge is
  /// (1) a Edge
  /// (2) an Arrow
  /// (3) inherited properties from QtRoundedEditRectItem
  boost::shared_ptr<QtEdge> m_qtedge;

  ///QtDialog that displays (1) a Edge
  boost::shared_ptr<QtEdgeDialog> m_qtedgedialog;

  ///QtDialog that displays (2) an Arrow

  ///QtDialog that displays (3) inherited properties from QtRoundedEditRectItem
  boost::shared_ptr<QtRoundedEditRectItemDialog> m_qtroundededitrectitem_dialog;

  //void OnDisplayStrategyChanged(QtEdge * const qtedge) noexcept;
  void OnEdgeChanged(QtEdge * const qtedge) noexcept;
  void OnQtRoundedRectItemChanged(QtEdge * const qtedge) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPQTEDGEDIALOG_H
