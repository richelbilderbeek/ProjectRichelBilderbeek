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
  class QtConceptMapQtNodeDialog;
}

namespace ribi {
namespace cmap {

class QtConceptMapQtNodeDialog : public ::ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtConceptMapQtNodeDialog(QWidget *parent = 0);
  QtConceptMapQtNodeDialog(const QtConceptMapQtNodeDialog&) = delete;
  QtConceptMapQtNodeDialog& operator=(const QtConceptMapQtNodeDialog&) = delete;
  ~QtConceptMapQtNodeDialog();

  void SetQtNode(const boost::shared_ptr<QtNode>& qtnode);
  boost::shared_ptr<QtNode> GetQtNode() const noexcept { return m_qtnode; }

private:
  Ui::QtConceptMapQtNodeDialog *ui;

  ///The QtNode to work on
  boost::shared_ptr<QtNode> m_qtnode;

  ///QtDialog that displays a Node (that is: a non-Qt Node)
  boost::shared_ptr<QtNodeDialog> m_qtnodedialog;

};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPQTNODEDIALOG_H
