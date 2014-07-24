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

///Tests all QtConceptMapConceptItem items when being a member of a cmap::QtEdge,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtConceptMapTestQtEdgeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:

public:
  explicit QtConceptMapTestQtEdgeDialog(QWidget *parent = 0);
  QtConceptMapTestQtEdgeDialog(const QtConceptMapTestQtEdgeDialog&) = delete;
  QtConceptMapTestQtEdgeDialog& operator=(const QtConceptMapTestQtEdgeDialog&) = delete;
  ~QtConceptMapTestQtEdgeDialog() noexcept;

  boost::shared_ptr<QtEdge> GetQtEdge() const noexcept;
  void SetQtEdge(const boost::shared_ptr<QtEdge>& qtnode) noexcept;

protected:

  void keyPressEvent(QKeyEvent *) noexcept override final;

private slots:

  void on_button_load_clicked() noexcept;

private:

  Ui::QtConceptMapTestQtEdgeDialog *ui;

  boost::shared_ptr<QtQtEdgeDialog> m_dialog_left;
  boost::shared_ptr<QtQtEdgeDialog> m_dialog_right;
  boost::shared_ptr< ::ribi::QtKeyboardFriendlyGraphicsView> m_view_left;
  boost::shared_ptr< ::ribi::QtKeyboardFriendlyGraphicsView> m_view_right;

  ///Tests invariants, will be empty in release version
  void CheckMe() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTQTEDGEDIALOG_H

