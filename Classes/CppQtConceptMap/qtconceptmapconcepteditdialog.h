#ifndef QTCONCEPTMAPCONCEPTEDITDIALOG_H
#define QTCONCEPTMAPCONCEPTEDITDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

struct QListWidgetItem;

namespace Ui { class QtConceptMapConceptEditDialog; }

namespace ribi {
namespace cmap {

class QtConceptMapConceptEditDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///concept is not const as user might want to modify it
  ///concept is only modified if user clicks OK
  explicit QtConceptMapConceptEditDialog(
    const boost::shared_ptr<ribi::cmap::Concept> concept,
    QWidget* parent = 0);
  QtConceptMapConceptEditDialog(const QtConceptMapConceptEditDialog&) = delete;
  QtConceptMapConceptEditDialog& operator=(const QtConceptMapConceptEditDialog&) = delete;
  ~QtConceptMapConceptEditDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void RemoveEmptyItem(QListWidgetItem * item);

  void on_button_add_clicked();

  ///Finally convert what the GUI displays to a Concept
  void on_button_ok_clicked();

private:
  Ui::QtConceptMapConceptEditDialog *ui;


#ifdef CONCEPTMAP_WRITE_TO_CONCEPT
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specificity;
#else
  ///The concept being modified, cannot be const
  const boost::shared_ptr<ribi::cmap::Concept> m_concept;

#endif

  ///Test this class
  static void Test() noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTEDITDIALOG_H
