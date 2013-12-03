#ifndef QTPVDBMENUDIALOG_H
#define QTPVDBMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbMenuDialog; }

namespace ribi {

namespace pvdb {

class QtPvdbMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbMenuDialog(QWidget* parent = 0);
  QtPvdbMenuDialog(const QtPvdbMenuDialog&) = delete;
  QtPvdbMenuDialog& operator=(const QtPvdbMenuDialog&) = delete;
  ~QtPvdbMenuDialog() noexcept;


  ///Test this class and all other QDialogs
  static void Test() noexcept;

public slots:
  void on_button_about_clicked() noexcept;
  void on_button_assessor_clicked() noexcept;
  void on_button_create_test_files_clicked() noexcept;
  void on_button_modify_stylesheet_clicked() noexcept;
  void on_button_overview_clicked() noexcept;
  void on_button_print_concept_map_clicked() noexcept;
  void on_button_print_rating_clicked() noexcept;
  void on_button_rate_concept_auto_clicked() noexcept;
  void on_button_rate_concept_clicked() noexcept;
  void on_button_rate_concept_map_clicked() noexcept;
  void on_button_rate_examples_clicked() noexcept;
  void on_button_rating_clicked() noexcept;
  void on_button_student_clicked() noexcept;
  void on_button_test_arrowitems_clicked() noexcept;
  void on_button_test_cluster_clicked() noexcept;
  //void on_button_test_conceptedit_clicked() noexcept;
  //void on_button_test_conceptitem_clicked() noexcept;
  //void on_button_test_conceptmap_clicked() noexcept;
  void on_button_test_create_sub_concept_map_clicked() noexcept;
  //void on_button_test_edge_item_clicked() noexcept;
  //void on_button_test_node_item_clicked() noexcept;
  void on_button_test_qtroundededitrectitem_clicked() noexcept;
  void on_button_test_qtroundedtextrectitem_clicked() noexcept;
  void on_button_view_files_clicked() noexcept;
  //void on_button_view_test_concept_maps_clicked() noexcept;

private slots:
  void keyPressEvent(QKeyEvent* e) noexcept;

  void on_button_test_conceptmap_2_clicked();

private:
  Ui::QtPvdbMenuDialog *ui;

  ///The file to work on
  boost::shared_ptr<pvdb::File> m_file;

  ///The mode at which the child dialogs are displayed
  bool m_show_child_dialogs_modal;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBMENUDIALOG_H
