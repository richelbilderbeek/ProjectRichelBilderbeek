#ifndef QTPVDBMENUDIALOG_H
#define QTPVDBMENUDIALOG_H

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbMenuDialog; }

namespace ribi {

namespace pvdb {

class QtPvdbMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbMenuDialog(QWidget* parent = 0);
  ~QtPvdbMenuDialog();


  ///Test this class and all other QDialogs
  static void Test();

public slots:
  void on_button_about_clicked();
  void on_button_assessor_clicked();
  void on_button_create_test_files_clicked();
  void on_button_modify_stylesheet_clicked();
  void on_button_overview_clicked();
  void on_button_print_concept_map_clicked();
  void on_button_print_rating_clicked();
  void on_button_rate_concept_auto_clicked();
  void on_button_rate_concept_clicked();
  void on_button_rate_concept_map_clicked();
  void on_button_rate_examples_clicked();
  void on_button_rating_clicked();
  void on_button_student_clicked();
  void on_button_test_arrowitems_clicked();
  void on_button_test_cluster_clicked();
  void on_button_test_conceptedit_clicked();
  void on_button_test_conceptitem_clicked();
  void on_button_test_conceptmap_clicked();
  void on_button_test_create_sub_concept_map_clicked();
  void on_button_test_edge_item_clicked();
  void on_button_test_node_item_clicked();
  void on_button_test_qtconceptmapdisplaywidget_clicked();
  void on_button_test_qtconceptmapeditwidget_clicked();
  void on_button_test_qtconceptmapratewidget_clicked();
  void on_button_test_qtroundededitrectitem_clicked();
  void on_button_test_qtroundedtextrectitem_clicked();
  void on_button_view_files_clicked();
  void on_button_view_test_concept_maps_clicked();

private slots:
  void keyPressEvent(QKeyEvent* e);

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
