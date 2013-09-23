#ifndef QTPVDBOVERVIEWWIDGET_H
#define QTPVDBOVERVIEWWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <QGraphicsView>
#include "pvdbfwd.h"
#pragma GCC diagnostic pop


namespace ribi {

struct QtHideAndShowDialog;

namespace pvdb {

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

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBOVERVIEWWIDGET_H
