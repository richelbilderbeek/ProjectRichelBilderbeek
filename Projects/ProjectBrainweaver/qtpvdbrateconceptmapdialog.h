#ifndef QTPVDBRATECONCEPTMAPDIALOG_H
#define QTPVDBRATECONCEPTMAPDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtpvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbRateConceptMapDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbRateConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbRateConceptMapDialog(
    boost::shared_ptr<pvdb::File> file,
    QWidget* parent = 0);
  QtPvdbRateConceptMapDialog(const QtPvdbRateConceptMapDialog&) = delete;
  QtPvdbRateConceptMapDialog& operator=(const QtPvdbRateConceptMapDialog&) = delete;
  ~QtPvdbRateConceptMapDialog() noexcept;

  cmap::QtConceptMapRateWidget * GetWidget();

  ///Respond to key press
  void keyPressEvent(QKeyEvent *);

  void Save();
  void Save(const std::string& filename);

private slots:
  void on_button_next_clicked();

  void on_button_save_clicked();

private:
  Ui::QtPvdbRateConceptMapDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;
  cmap::QtConceptMapRateWidget * const m_widget;

  ///The widget requested for a rating of the already supplied sub concept map,
  ///with the focal concept item as the central node
  void OnRequestRateConceptDialog(const boost::shared_ptr<ribi::cmap::ConceptMap> sub_concept_map);

  static void Test();
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBRATECONCEPTMAPDIALOG_H
