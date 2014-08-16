#ifndef QTTESTQTROUNDEDRECTITEMWIDGET_H
#define QTTESTQTROUNDEDRECTITEMWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkeyboardfriendlygraphicsview.h"
#pragma GCC diagnostic pop

namespace ribi {

///The widget holding the items
///Yes, really use a widget, otherwise the keyPressEvents cannot be forwarded
struct QtTestQtRoundedRectItemWidget : public ribi::QtKeyboardFriendlyGraphicsView
{
  QtTestQtRoundedRectItemWidget(QWidget *parent = 0);
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDRECTITEMWIDGET_H
