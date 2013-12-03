#ifndef QTTESTCONCEPTAMPMENUDIALOG_H
#define QTTESTCONCEPTAMPMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestConceptMapMenuDialog;
}

namespace ribi {
namespace cmap {

class QtTestConceptMapMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestConceptMapMenuDialog(QWidget *parent = 0);
  QtTestConceptMapMenuDialog(const QtTestConceptMapMenuDialog&) = delete;
  QtTestConceptMapMenuDialog& operator=(const QtTestConceptMapMenuDialog&) = delete;
  ~QtTestConceptMapMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_readonly_conceptmap_clicked();

  void on_button_edit_conceptmap_clicked();

  void on_button_rate_conceptmap_clicked();

  void on_button_concept_clicked();

  void on_button_node_clicked();

  void on_button_edge_clicked();

  void on_button_view_concept_maps_clicked();

private:
  Ui::QtTestConceptMapMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTTESTCONCEPTAMPMENUDIALOG_H
