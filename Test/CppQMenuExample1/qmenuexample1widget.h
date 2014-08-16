#ifndef QMENUEXAMPLE1WIDGET_H
#define QMENUEXAMPLE1WIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QWidget>
#pragma GCC diagnostic pop

class QMenuExample1Widget : public QWidget
{
  Q_OBJECT
public:
  explicit QMenuExample1Widget(QWidget *parent = 0);

signals:

public slots:

private slots:
  void OnShowPopUpMenu(const QPoint& pos);
  void OnClickPopUpMenu();

};

#endif // QMENUEXAMPLE1WIDGET_H
