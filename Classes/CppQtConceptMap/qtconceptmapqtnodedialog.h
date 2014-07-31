#ifndef QTCONCEPTMAPQTNODEDIALOG_H
#define QTCONCEPTMAPQTNODEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop


namespace Ui {
  class QtQtNodeDialog;
}

namespace ribi {
namespace cmap {

class QtQtNodeDialog : public ::ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtQtNodeDialog(QWidget *parent = 0);
  QtQtNodeDialog(const QtQtNodeDialog&) = delete;
  QtQtNodeDialog& operator=(const QtQtNodeDialog&) = delete;
  ~QtQtNodeDialog();


  static int GetMinimumHeight(const QtNode& qtnode) noexcept;
  boost::shared_ptr<QtNode> GetQtNode() const noexcept { return m_qtnode; }

  ///Read the name from the GUI
  std::string GetUiName() const noexcept;

  void SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept;

  ///Set the name via the GUI
  void SetUiName(const std::string& name) const noexcept;

private:
  Ui::QtQtNodeDialog *ui;

  ///The QtNode to work on
  ///A QtNode is
  /// (1) a Node
  /// (2) inherited properties from QtRoundedEditRectItem
  boost::shared_ptr<QtNode> m_qtnode;

  ///QtDialog that displays (1) a Node
  boost::shared_ptr<QtNodeDialog> m_qtnodedialog;

  ///QtDialog that displays (2) inherited properties from QtRoundedEditRectItem
  boost::shared_ptr<QtRoundedEditRectItemDialog> m_qtroundededitrectitem_dialog;

  ///Checks invariants, empty at release version
  void CheckMe() const noexcept;

  //void OnDisplayStrategyChanged(QtNode * const qtnode) noexcept;
  void OnNodeChanged(QtNode * const qtnode) noexcept;
  void OnQtRoundedRectItemChanged(QtNode * const qtnode) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPQTNODEDIALOG_H
