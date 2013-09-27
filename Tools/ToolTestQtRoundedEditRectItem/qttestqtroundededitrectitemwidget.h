#ifndef QTTESTQTROUNDEDEDITRECTITEMWIDGETWIDGET_H
#define QTTESTQTROUNDEDEDITRECTITEMWIDGETWIDGET_H

#include "qtkeyboardfriendlygraphicsview.h"

struct QFont;

namespace ribi {

///The widget holding the items
struct QtTestQtRoundedEditRectItemWidget : public QtKeyboardFriendlyGraphicsView
{
  QtTestQtRoundedEditRectItemWidget(QWidget *parent = 0);

  void keyPressEvent(QKeyEvent *event) noexcept;

private:
  ///Display a font
  void Display(const QFont& font);
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDEDITRECTITEMWIDGETWIDGET_H
