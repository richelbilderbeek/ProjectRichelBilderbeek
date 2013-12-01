#ifndef QTPVDBCONCEPTMAPDIALOG_H
#define QTPVDBCONCEPTMAPDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtpvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbConceptMapDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbConceptMapDialog : public ::ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbConceptMapDialog(const boost::shared_ptr<File> file, QWidget* parent = 0);
  QtPvdbConceptMapDialog(const QtPvdbConceptMapDialog&) = delete;
  QtPvdbConceptMapDialog& operator=(const QtPvdbConceptMapDialog&) = delete;
  ~QtPvdbConceptMapDialog() noexcept;

  #ifndef NDEBUG
  ///Do random stuff, for example, add a node and an edge (used for debugging)
  void DoRandomStuff();
  #endif

  ///Obtain the widget
  const cmap::QtConceptMapWidget * GetWidget() const;
  cmap::QtConceptMapWidget * GetWidget();

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  ///Save to m_file
  void Save() const;

  ///Save to disk
  void Save(const std::string& filename) const;

  #ifndef NDEBUG
  ///Shuffle to concepts (used for debugging)
  void Shuffle();
  #endif

  private slots:

  void keyPressEvent(QKeyEvent *);
  void on_button_save_clicked();
  void on_button_print_clicked();

  //void on_button_test_clicked();

private:
  Ui::QtPvdbConceptMapDialog *ui;

  ///Must we go back to the student menu?
  bool m_back_to_menu;

  ///The file
  boost::shared_ptr<pvdb::File> m_file;

  ///The concept map widget
  cmap::QtConceptMapEditWidget * const m_widget;

  static const boost::shared_ptr<ribi::cmap::ConceptMap> CreateFromCluster(
    const std::string& question,
    const boost::shared_ptr<Cluster>& cluster);

  //static QtPvdbConceptMapEditWidget * CreateWidget(const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map);
  ///DON'T USE: puts a new ConceptMap in file
  static cmap::QtConceptMapEditWidget * CreateWidget(const boost::shared_ptr<pvdb::File> file);

  ///NEW 2013-01-07
  void OnConceptMapItemRequestsEdit(cmap::QtConceptMapItem* const item);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBCONCEPTMAPDIALOG_H
