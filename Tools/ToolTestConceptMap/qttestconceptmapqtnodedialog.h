#ifndef QTCONCEPTMAPTESTQTNODEDIALOG_H
#define QTCONCEPTMAPTESTQTNODEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestQtNodeDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items when being a member of a QtNode,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestQtNodeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestQtNodeDialog(QWidget *parent = 0);
  QtTestQtNodeDialog(const QtTestQtNodeDialog&) = delete;
  QtTestQtNodeDialog& operator=(const QtTestQtNodeDialog&) = delete;
  ~QtTestQtNodeDialog() noexcept;


  boost::shared_ptr<QtNode> GetQtNode() const noexcept;
  QImage GetUiView() const noexcept;

  void SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept;

protected:

  void keyPressEvent(QKeyEvent *) noexcept override final;

private slots:

  void on_button_load_clicked() noexcept;

private:

  Ui::QtTestQtNodeDialog *ui;

  boost::shared_ptr<QtQtNodeDialog> m_dialog_left;
  boost::shared_ptr<QtQtNodeDialog> m_dialog_right;
  boost::shared_ptr< ::ribi::QtKeyboardFriendlyGraphicsView> m_view_left;
  boost::shared_ptr< ::ribi::QtKeyboardFriendlyGraphicsView> m_view_right;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTQTNODEDIALOG_H
