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

namespace Ui { class QtConceptMapTestQtNodeDialog; }

struct QGraphicsView;

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items when being a member of a QtNode,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtConceptMapTestQtNodeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtConceptMapTestQtNodeDialog(QWidget *parent = 0);
  QtConceptMapTestQtNodeDialog(const QtConceptMapTestQtNodeDialog&) = delete;
  QtConceptMapTestQtNodeDialog& operator=(const QtConceptMapTestQtNodeDialog&) = delete;
  ~QtConceptMapTestQtNodeDialog() noexcept;

  boost::shared_ptr<QtNode> GetQtNode() const noexcept;
  void SetQtNode(const boost::shared_ptr<QtNode>& qtnode) noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  //void on_box_competency_currentIndexChanged(int index);
  //void on_edit_name_textChanged(const QString &arg1);
  //void on_box_complexity_currentIndexChanged(const QString &arg1);
  //void on_box_concreteness_currentIndexChanged(const QString &arg1);
  //void on_box_specificity_currentIndexChanged(const QString &arg1);
  //void on_edit_example_text_textChanged(const QString &arg1);

  void on_button_load_clicked();

private:

  Ui::QtConceptMapTestQtNodeDialog *ui;

  boost::shared_ptr<QtQtNodeDialog> m_dialog_left;
  boost::shared_ptr<QtQtNodeDialog> m_dialog_right;
  boost::shared_ptr<QGraphicsView> m_view_left;
  boost::shared_ptr<QGraphicsView> m_view_right;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTQTNODEDIALOG_H
