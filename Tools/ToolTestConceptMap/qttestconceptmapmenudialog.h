#ifndef QTTESTCONCEPTAMPMENUDIALOG_H
#define QTTESTCONCEPTAMPMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestMenuDialog;
}

namespace ribi {
namespace cmap {

class QtTestMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestMenuDialog(QWidget *parent = 0);
  QtTestMenuDialog(const QtTestMenuDialog&) = delete;
  QtTestMenuDialog& operator=(const QtTestMenuDialog&) = delete;
  ~QtTestMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_concept_clicked();
  void on_button_edge_clicked();
  void on_button_edit_conceptmap_clicked();
  void on_button_example_clicked();
  void on_button_examples_clicked();
  void on_button_node_clicked();
  void on_button_qtedge_clicked();
  void on_button_qtnode_clicked();
  void on_button_quit_clicked();
  void on_button_view_conceptmaps_clicked();

private:
  Ui::QtTestMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTAMPMENUDIALOG_H
