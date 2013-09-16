#ifndef QTLABELEDQUADBEZIERARROWITEM_H
#define QTLABELEDQUADBEZIERARROWITEM_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

//#include <QFont>
#include "qtroundedtextrectitem.h"
//#include "qtquadbezierarrowitem.h"
#pragma GCC diagnostic pop

namespace ribi {

struct QtQuadBezierArrowItem;

///The QtLabeledQuadBezierArrowItem is a QtRoundedTextRectItem that
///draws a bezier curve underneath itself, between head and tail arrowhead
struct QtLabeledQuadBezierArrowItem : public QtRoundedTextRectItem
{

  QtLabeledQuadBezierArrowItem(
    const QGraphicsItem *const from,
    const bool tail,
    const std::string& text,
    const bool head,
    const QGraphicsItem *const to,
    QGraphicsItem *parent = 0);

  const boost::shared_ptr<const QtQuadBezierArrowItem>  GetArrow() const { return m_arrow; }
  const boost::shared_ptr<      QtQuadBezierArrowItem>& GetArrow()       { return m_arrow; }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

protected:
  virtual QRectF boundingRect() const;
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
  const boost::shared_ptr<QtQuadBezierArrowItem> m_arrow;

};

} //~namespace ribi

#endif // QTLABELEDQUADBEZIERARROWITEM_H
