#ifndef QTWIDGET_H
#define QTWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsView>
#pragma GCC diagnostic pop

///Forward declaration
struct QtHighlighter;

struct QtWidget : public QGraphicsView
{
  QtWidget();

  protected:
  void mouseMoveEvent(QMouseEvent *event);

  private:
  ///Class highlighting a QGraphicsItem
  QtHighlighter * const m_highlighter;
};

#endif // QTWIDGET_H
