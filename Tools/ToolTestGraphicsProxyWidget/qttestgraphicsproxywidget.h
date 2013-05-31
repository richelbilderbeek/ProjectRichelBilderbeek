#ifndef QTBOUNCINGBALLSWIDGET_H
#define QTBOUNCINGBALLSWIDGET_H

#include <QGraphicsView>

struct QGraphicsScene;
struct SomeDialog;

struct QtTestGraphicsProxyWidget : public QGraphicsView
{
  QtTestGraphicsProxyWidget(QWidget *parent = 0);


  protected:
  void resizeEvent(QResizeEvent *event);

  private:
  QGraphicsScene * const m_scene;
  //Proxies of the added widgets
  std::vector<QGraphicsProxyWidget *> m_proxies;
  std::vector<SomeDialog *> m_dialogs;

};

#endif // QTBOUNCINGBALLSWIDGET_H
