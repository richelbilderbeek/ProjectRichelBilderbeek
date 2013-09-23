#ifndef QTPVDBCREATEASSESSMENTCOMPLETEDIALOG_H
#define QTPVDBCREATEASSESSMENTCOMPLETEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbCreateAssessmentCompleteDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbCreateAssessmentCompleteDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbCreateAssessmentCompleteDialog(QWidget* parent = 0);
  QtPvdbCreateAssessmentCompleteDialog(const QtPvdbCreateAssessmentCompleteDialog&) = delete;
  QtPvdbCreateAssessmentCompleteDialog& operator=(const QtPvdbCreateAssessmentCompleteDialog&) = delete;
  ~QtPvdbCreateAssessmentCompleteDialog() noexcept;

  ///Get the filled in concept map focal question
  const std::string GetQuestion() const;

  ///Must the parent go back to the menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  ///Save file to disk
  void Save(const std::string& filename) const;

  ///Fill in the concept map focal question
  void SetQuestion(const std::string& question);

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_save_clicked();

  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtPvdbCreateAssessmentCompleteDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBCREATEASSESSMENTCOMPLETEDIALOG_H
