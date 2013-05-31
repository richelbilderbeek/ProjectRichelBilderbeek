#ifndef QTPVDBCONCEPTEDITDIALOG_H
#define QTPVDBCONCEPTEDITDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif

struct QListWidgetItem;

namespace Ui {
class QtPvdbConceptEditDialog;
}


class QtPvdbConceptEditDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///concept is not const as user might want to modify it
  ///concept is only modified if user clicks OK
  explicit QtPvdbConceptEditDialog(
    const boost::shared_ptr<pvdb::Concept> concept,
    QWidget* parent = 0);
  ~QtPvdbConceptEditDialog();

#ifdef PVDB_WRITE_TO_CONCEPT
  const boost::shared_ptr<pvdb::Concept> WriteToConcept() const;
#endif

#ifndef PVDB_USE_ONLY_NEEDED
  //const std::string GetName() const { return m_name; }
#endif


protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void RemoveEmptyItem(QListWidgetItem * item);

  void on_button_add_clicked();

  ///Finally convert what the GUI displays to a Concept
  void on_button_ok_clicked();

private:
  Ui::QtPvdbConceptEditDialog *ui;


#ifdef PVDB_WRITE_TO_CONCEPT
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specificity;
#else
  ///The concept being modified, cannot be const
  const boost::shared_ptr<pvdb::Concept> m_concept;

#endif

  ///Test this class
  static void Test();
};

#endif // QTPVDBCONCEPTEDITDIALOG_H
