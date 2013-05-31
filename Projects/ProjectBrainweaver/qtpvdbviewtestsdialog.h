#ifndef QTPVDBVIEWTESTSDIALOG_H
#define QTPVDBVIEWTESTSDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

namespace Ui {
class QtPvdbViewTestsDialog;
}

class QtPvdbViewTestsDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbViewTestsDialog(QWidget* parent = 0);
  ~QtPvdbViewTestsDialog();

protected:
  void keyPressEvent(QKeyEvent* event);
  
private:
  Ui::QtPvdbViewTestsDialog *ui;
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > m_v;
};

#endif // QTPVDBVIEWTESTSDIALOG_H
