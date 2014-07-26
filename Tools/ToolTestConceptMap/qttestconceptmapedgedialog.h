#ifndef QTCONCEPTMAPTESTEDGEDIALOG_H
#define QTCONCEPTMAPTESTEDGEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestEdgeDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items, especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestEdgeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestEdgeDialog(QWidget *parent = 0);
  QtTestEdgeDialog(const QtTestEdgeDialog&) = delete;
  QtTestEdgeDialog& operator=(const QtTestEdgeDialog&) = delete;
  ~QtTestEdgeDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *event);
  
private slots:

  //void on_box_competency_currentIndexChanged(int index);
  //void on_edit_name_textChanged(const QString &arg1);
  //void on_box_complexity_currentIndexChanged(const QString &arg1);
  //void on_box_concreteness_currentIndexChanged(const QString &arg1);
  //void on_box_specificity_currentIndexChanged(const QString &arg1);
  //void on_edit_example_text_textChanged(const QString &arg1);

  void on_button_load_clicked();

private:
  Ui::QtTestEdgeDialog *ui;

  boost::shared_ptr<Node> m_from_node;
  boost::shared_ptr<QtEdgeDialog> m_qtedgedialog_1;
  boost::shared_ptr<QtEdgeDialog> m_qtedgedialog_2;
  boost::shared_ptr<Node> m_to_node;

  //const boost::shared_ptr<Node> m_concept;
  //cmap::QtDisplayStrategy* m_display_concept;
  //cmap::QtEditStrategy* m_edit_concept;
  //cmap::QtRateStrategy* m_rate_concept;

  ///Get the Node via the route chosen by box_edit
  //const boost::shared_ptr<Node> GetChosenNode();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDGEDIALOG_H
