#ifndef QTAUTORESIZELISTWIDGET_H
#define QTAUTORESIZELISTWIDGET_H

#include <QListWidget>

struct QtAutoResizeListWidget : public QListWidget
{
  QtAutoResizeListWidget(QWidget *parent = 0);
  void addItem(QListWidgetItem *item);

  private:
  QTimer * const m_timer;

  void OnTimer();
};

#endif // QTAUTORESIZELISTWIDGET_H
