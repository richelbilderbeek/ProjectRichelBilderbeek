#ifndef QTPVDBCLUSTERDIALOG_H
#define QTPVDBCLUSTERDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "qtpvdbclusterwidget.h"
#include "pvdbfile.h"
#endif


namespace Ui { class QtPvdbClusterDialog; }

///The Dialog in which the user clusters concepts and examples
class QtPvdbClusterDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPvdbClusterDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  ~QtPvdbClusterDialog();

  ///Do some random stuff, e.g. adding some concepts with examples
  void DoRandomStuff();

  ///Obtain the widget
  QtPvdbClusterWidget * GetWidget();
  const QtPvdbClusterWidget * GetWidget() const;

  ///Does the dialog want to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  //Save to disk
  void Save(const std::string& filename);


protected:
  //Respond to the following keys:
  //F2: edit current item
  //Delete: remove current item
  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_add_clicked();
  void on_button_next_clicked();
  void on_edit_textChanged(const QString &arg1);

  void on_button_save_clicked();

private:
  Ui::QtPvdbClusterDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  boost::shared_ptr<pvdb::File> m_file;

  //Start saving procedure, with request of filename
  void Save();

  ///Test this class
  static void Test();
};

#endif // QTPVDBCLUSTERDIALOG_H
