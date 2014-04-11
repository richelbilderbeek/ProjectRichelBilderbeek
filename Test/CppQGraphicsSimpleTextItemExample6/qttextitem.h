#ifndef QTTEXTITEM_H
#define QTTEXTITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/shared_ptr.hpp>
#include <QGraphicsSimpleTextItem>
#pragma GCC diagnostic pop

struct Text;

struct QtTextItem : public QGraphicsSimpleTextItem
{
  QtTextItem(const boost::shared_ptr<const Text> text,
    QGraphicsItem *parent = 0
  );

  private:
  ///Read-only Text
  const boost::shared_ptr<const Text> m_text;

  //Respond to a change of Text
  void OnTextChanged();
};

#endif // QTTEXTITEM_H
