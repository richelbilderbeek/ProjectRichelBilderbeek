#ifndef QTPVDBRATECONCEPTMAPDIALOG_H
#define QTPVDBRATECONCEPTMAPDIALOG_H

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
  static void Test();
};

#endif // QTPVDBRATECONCEPTMAPDIALOG_H
