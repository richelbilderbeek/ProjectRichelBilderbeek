#ifndef QTCONCEPTMAPTESTNODEITEMDIALOG_H
#define QTCONCEPTMAPTESTNODEITEMDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapTestNodeItemDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items when being a member of a cmap::QtNode,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtConceptMapTestNodeItemDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtConceptMapTestNodeItemDialog(QWidget *parent = 0);
  QtConceptMapTestNodeItemDialog(const QtConceptMapTestNodeItemDialog&) = delete;
  QtConceptMapTestNodeItemDialog& operator=(const QtConceptMapTestNodeItemDialog&) = delete;
  ~QtConceptMapTestNodeItemDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_box_competency_currentIndexChanged(int index);
  void on_edit_name_textChanged(const QString &arg1);
  void on_box_complexity_currentIndexChanged(const QString &arg1);
  void on_box_concreteness_currentIndexChanged(const QString &arg1);
  void on_box_specificity_currentIndexChanged(const QString &arg1);
  void on_edit_example_text_textChanged(const QString &arg1);

private:

  Ui::QtConceptMapTestNodeItemDialog *ui;
  const boost::shared_ptr<Node> m_node;
  cmap::QtNode* m_display_node;
  cmap::QtNode* m_edit_node;
  cmap::QtNode* m_rate_node;

  ///Get the Node via the route chosen by box_edit
  const boost::shared_ptr<Node> GetNode();

  void OnRequestsSceneUpdate();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTCONCEPTMAPTESTNODEITEMDIALOG_H
