#ifndef QTRICHELBILDERBEEKMENUITEMWIDGET_H
#define QTRICHELBILDERBEEKMENUITEMWIDGET_H

#include "qtkeyboardfriendlygraphicsview.h"

///The widget holding the items
struct QtRichelBilderbeekMenuItemWidget : public QtKeyboardFriendlyGraphicsView
{
  QtRichelBilderbeekMenuItemWidget(QWidget *parent = 0);

  void keyPressEvent(QKeyEvent *event);
};

#endif // QTRICHELBILDERBEEKMENUITEMWIDGET_H
