#ifndef QTPVDBRATECONCEPTMAPDIALOG_H
#define QTPVDBRATECONCEPTMAPDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbfile.h"
#endif

namespace Ui {
class QtPvdbRateConceptMapDialog;
}

class QtPvdbRateConceptMapDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbRateConceptMapDialog(
    boost::shared_ptr<pvdb::File> file,
    QWidget* parent = 0);

  ~QtPvdbRateConceptMapDialog();

  QtPvdbConceptMapRateWidget * GetWidget();

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
  QtPvdbConceptMapRateWidget * const m_widget;

  ///The widget requested for a rating of the already supplied sub concept map,
  ///with the focal concept item as the central node
  void OnRequestRateConceptDialog(const boost::shared_ptr<pvdb::ConceptMap> sub_concept_map);

  static void Test();
};

#endif // QTPVDBRATECONCEPTMAPDIALOG_H
