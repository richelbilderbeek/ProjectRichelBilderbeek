#ifndef QTPVDBRATEEXAMPLESDIALOG_H
#define QTPVDBRATEEXAMPLESDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui {
  class QtPvdbRateExamplesDialog;
}

namespace ribi {
namespace pvdb {

///Allows the user to rate the examples of a concept
class QtPvdbRateExamplesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbRateExamplesDialog(
    const boost::shared_ptr<ribi::pvdb::Concept> concept,
    QWidget* parent = 0);
  QtPvdbRateExamplesDialog(const QtPvdbRateExamplesDialog&) = delete;
  QtPvdbRateExamplesDialog& operator=(const QtPvdbRateExamplesDialog&) = delete;
  ~QtPvdbRateExamplesDialog();

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
  Ui::QtPvdbRateExamplesDialog *ui;

  ///The concept, which is modified when clicking OK, but remains unmodified when
  ///the user clicks cancel
  const boost::shared_ptr<ribi::pvdb::Concept> m_concept;

  ///Obtain the rated examples
  const boost::shared_ptr<ribi::pvdb::Examples> GetRatedExamples() const;

  ///Test this class
  static void Test();

};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBRATEEXAMPLESDIALOG_H
