#ifndef QTPVDBOVERVIEWWIDGET_H
#define QTPVDBOVERVIEWWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>


#include <QGraphicsView>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
struct QtHideAndShowDialog;
#else
#include "qthideandshowdialog.h"
#endif


class QtPvdbOverviewWidget : public QGraphicsView
{
  Q_OBJECT

public:

  explicit QtPvdbOverviewWidget(QWidget* parent = 0);
    
public slots:

  void mouseDoubleClickEvent(QMouseEvent *event);

private:

  ///Create all dialogs
  static const std::vector<QtHideAndShowDialog* > GetAllDialogs();

  ///NASTY BUG ALERT: It crashes Wine if m_dialogs is created as
  ///const std::vector<boost::shared_ptr<QtHideAndShowDialog> > m_dialogs;
  ///No idea why...
  const std::vector<QtHideAndShowDialog* > m_dialogs;

};

#endif // QTPVDBOVERVIEWWIDGET_H
