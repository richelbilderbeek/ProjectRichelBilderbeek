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

  void SetQtNode(const boost::shared_ptr<QtNode>& qtnode);
  boost::shared_ptr<QtNode> GetQtNode() const noexcept { return m_qtnode; }

private:
  Ui::QtQtNodeDialog *ui;

  ///The QtNode to work on
  boost::shared_ptr<QtNode> m_qtnode;

  ///QtDialog that displays a Node (that is: a non-Qt Node)
  boost::shared_ptr<QtNodeDialog> m_qtnodedialog;

};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPQTNODEDIALOG_H
