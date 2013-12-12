#ifndef QTCONCEPTMAPRATEEXAMPLESDIALOG_H
#define QTCONCEPTMAPRATEEXAMPLESDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtRateExamplesDialog; }

namespace ribi {
namespace cmap {

///Allows the user to rate the examples of a concept
class QtRateExamplesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtRateExamplesDialog(
    const boost::shared_ptr<ribi::cmap::Concept> concept,
    QWidget* parent = 0);
  QtRateExamplesDialog(const QtRateExamplesDialog&) = delete;
  QtRateExamplesDialog& operator=(const QtRateExamplesDialog&) = delete;
  ~QtRateExamplesDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_prof_clicked();
  void on_button_organisations_clicked();
  void on_button_social_clicked();
  void on_button_target_audience_clicked();
  void on_button_prof_development_clicked();
  void on_button_misc_clicked();
  void on_button_ti_knowledge_clicked();
  void on_button_ok_clicked();

private:
  Ui::QtRateExamplesDialog *ui;

  ///The concept, which is modified when clicking OK, but remains unmodified when
  ///the user clicks cancel
  const boost::shared_ptr<ribi::cmap::Concept> m_concept;

  ///Obtain the rated examples
  const boost::shared_ptr<ribi::cmap::Examples> GetRatedExamples() const;

  ///Test this class
  static void Test() noexcept;

};

} //~namespace pvdb
} //~namespace ribi

#endif // QTCONCEPTMAPRATEEXAMPLESDIALOG_H
