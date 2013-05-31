#ifndef QTPVDBMENUDIALOG_H
#define QTPVDBMENUDIALOG_H

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbfile.h"
#endif

namespace Ui { class QtPvdbMenuDialog; }

class QtPvdbMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbMenuDialog(QWidget* parent = 0);
  ~QtPvdbMenuDialog();

  ///Test this class and all other QDialogs
  static void Test();

protected:
  //void closeEvent(QCloseEvent * event) { QtHideAndShowDialog::closeEvent(event); }

private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_assessor_clicked();

  void on_button_student_clicked();

  void on_button_test_cluster_clicked();

  void on_button_overview_clicked();

  void on_button_about_clicked();

  void on_button_test_conceptmap_clicked();

  void on_button_test_conceptedit_clicked();

  void on_button_view_files_clicked();

  void on_button_view_test_concept_maps_clicked();

  void on_button_rate_concept_map_clicked();

  void on_button_rate_concept_clicked();

  void on_button_rate_examples_clicked();

  void on_button_rating_clicked();

  void on_button_concept_clicked();

  void on_button_test_node_item_clicked();


  void on_button_test_qtroundedtextrectitem_clicked();

  void on_button_test_qtroundededitrectitem_clicked();

  void on_button_test_edge_item_clicked();

  void on_button_test_arrowitems_clicked();

  void on_button_test_qtconceptmapeditwidget_clicked();

  void on_button_test_qtconceptmapratewidget_clicked();

  void on_button_create_test_files_clicked();

  void on_button_modify_stylesheet_clicked();

private:
  Ui::QtPvdbMenuDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;
};


#endif // QTPVDBMENUDIALOG_H
