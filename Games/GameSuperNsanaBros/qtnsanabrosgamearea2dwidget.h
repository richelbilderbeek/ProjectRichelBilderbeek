#ifndef QTNSANABROSGAMEAREA2DWIDGET_H
#define QTNSANABROSGAMEAREA2DWIDGET_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
//#include <QTimer>
#include <QWidget>
//---------------------------------------------------------------------------
#include "nsanabrosstlfwdheader.h"
//struct NsanaBrosGame;
//struct NsanaBrosGameArea2dWidget;
//struct QTimer;
#include "nsanabrosqtheader.h" //WHY?
//---------------------------------------------------------------------------
class QtNsanaBrosGameArea2dWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtNsanaBrosGameArea2dWidget(
    NsanaBrosGame * const game = 0,
    QWidget *parent = 0);
  void Repaint();

protected:
  void paintEvent(QPaintEvent *);

signals:

public slots:

private:

  const NsanaBrosGame * const m_game;
};
//---------------------------------------------------------------------------
#endif // QTNSANABROSGAMEAREA2DWIDGET_H
