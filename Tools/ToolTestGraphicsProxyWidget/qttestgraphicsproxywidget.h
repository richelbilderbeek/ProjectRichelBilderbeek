#ifndef QTBOUNCINGBALLSWIDGET_H
#define QTBOUNCINGBALLSWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QtSomeDialog;

struct QtTestGraphicsProxyWidget : public QGraphicsView
{
  QtTestGraphicsProxyWidget(QWidget *parent = 0);


  protected:
  void resizeEvent(QResizeEvent *event);

  private:
  std::vector<QtSomeDialog *> m_dialogs;

  //Proxies of the added widgets
  std::vector<QGraphicsProxyWidget *> m_proxies;
  QGraphicsScene * const m_scene;

};

#endif // QTBOUNCINGBALLSWIDGET_H
