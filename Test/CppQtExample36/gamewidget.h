#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class GameWidget : public QWidget
{
  Q_OBJECT

  public:
  GameWidget();
  void paintEvent(QPaintEvent *);

  private:
  int m_x;
  int m_y;

  private slots:
  ///Responds to internal QTimer
  void OnTimer();
};

#endif // GAMEWIDGET_H
