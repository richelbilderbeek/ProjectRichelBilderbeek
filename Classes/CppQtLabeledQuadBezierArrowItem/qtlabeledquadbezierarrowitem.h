#ifndef QTLABELEDQUADBEZIERARROWITEM_H
#define QTLABELEDQUADBEZIERARROWITEM_H

#include <string>
#include <boost/signals2.hpp>
#include <QFont>
#include "qtroundedtextrectitem.h"
#include "qtquadbezierarrowitem.h"


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
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

protected:
  virtual QRectF boundingRect() const;
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
  const boost::shared_ptr<QtQuadBezierArrowItem> m_arrow;

};

#endif // QTLABELEDQUADBEZIERARROWITEM_H
