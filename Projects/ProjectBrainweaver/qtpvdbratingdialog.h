#ifndef QTPVDBRATINGDIALOG_H
#define QTPVDBRATINGDIALOG_H

#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbRatingDialog; }

struct QTableWidget;

namespace ribi {

namespace pvdb {

///View the current rating, optimized for humans
///QtPvdbPrintRatingDialog is optimized for printers
class QtPvdbRatingDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

  public:
  explicit QtPvdbRatingDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  ~QtPvdbRatingDialog();

  bool GetBackToMenu() const { return m_back_to_menu; }

  private slots:
  void on_button_save_clicked();
  void keyPressEvent(QKeyEvent* e);

  void on_button_print_clicked();

  void on_edit_name_textEdited(const QString &arg1);

private:
  Ui::QtPvdbRatingDialog *ui;
  bool m_back_to_menu;
  boost::shared_ptr<pvdb::File> m_file;

  void Save(const std::string& filename) const;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBRATINGDIALOG_H
