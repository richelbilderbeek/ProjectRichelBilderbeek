#ifndef QTPVDBCONCEPTMAPDIALOG_H
#define QTPVDBCONCEPTMAPDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "qtpvdbconceptmapwidget.h"
#include "pvdbfile.h"
#endif

namespace Ui { class QtPvdbConceptMapDialog; }

class QtPvdbConceptMapDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbConceptMapDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);

  ~QtPvdbConceptMapDialog();

  ///Do random stuff, for example, add a node and an edge (used for debugging)
  void DoRandomStuff();

  ///Obtain the widget
  const QtPvdbConceptMapWidget * GetWidget() const;
  QtPvdbConceptMapWidget * GetWidget();

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  ///Save to m_file
  void Save() const;

  ///Save to disk
  void Save(const std::string& filename) const;

  ///Shuffle to concepts (used for debugging)
  void Shuffle();

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
  QtPvdbConceptMapEditWidget * const m_widget;

  static QtPvdbConceptMapEditWidget * CreateWidget(const boost::shared_ptr<pvdb::File> file);

  ///NEW 2013-01-07
  void OnConceptMapItemRequestsEdit(QtPvdbConceptMapItem* const item);

  ///Test this class
  static void Test();
};


#endif // QTPVDBCONCEPTMAPDIALOG_H
