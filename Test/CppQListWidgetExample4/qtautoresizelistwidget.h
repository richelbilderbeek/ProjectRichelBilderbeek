#ifndef QTAUTORESIZELISTWIDGET_H
#define QTAUTORESIZELISTWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QListWidget>
#pragma GCC diagnostic pop

struct QtAutoResizeListWidget : public QListWidget
{
  QtAutoResizeListWidget(QWidget *parent = 0);
  QtAutoResizeListWidget(const QtAutoResizeListWidget&) = delete;
  QtAutoResizeListWidget& operator=(const QtAutoResizeListWidget&) = delete;
  void addItem(QListWidgetItem *item);

  private:
  QTimer * const m_timer;

  void OnTimer();
};

#endif // QTAUTORESIZELISTWIDGET_H
