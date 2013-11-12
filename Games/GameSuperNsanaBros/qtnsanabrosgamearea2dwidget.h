#ifndef QTNSANABROSGAMEAREA2DWIDGET_H
#define QTNSANABROSGAMEAREA2DWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

//#include <QTimer>
#include <QWidget>

#include "nsanabrosstlfwdheader.h"
//struct NsanaBrosGame;
//struct NsanaBrosGameArea2dWidget;
//struct QTimer;
#include "nsanabrosqtheader.h" //WHY?
#pragma GCC diagnostic pop

namespace ribi {

class QtNsanaBrosGameArea2dWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtNsanaBrosGameArea2dWidget(
    NsanaBrosGame * const game = 0,
    QWidget *parent = 0);
  QtNsanaBrosGameArea2dWidget(const QtNsanaBrosGameArea2dWidget&) = delete;
  QtNsanaBrosGameArea2dWidget& operator=(const QtNsanaBrosGameArea2dWidget&) = delete;
  void Repaint();

protected:
  void paintEvent(QPaintEvent *);

signals:

public slots:

private:

  const NsanaBrosGame * const m_game;
};

} //~namespace ribi

#endif // QTNSANABROSGAMEAREA2DWIDGET_H
