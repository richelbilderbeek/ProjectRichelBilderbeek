#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "qttextitem.h"

#include <cassert>
#include "text.h"
#pragma GCC diagnostic pop

QtTextItem::QtTextItem(
  const boost::shared_ptr<const Text> text,
  QGraphicsItem *parent
) : QGraphicsSimpleTextItem(parent),
    m_text(text)
{
  this->setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsMovable);

  m_text->m_signal_text_changed.connect(
    boost::bind(&QtTextItem::OnTextChanged,this));

  this->setText(m_text->GetText().c_str());
}

void QtTextItem::OnTextChanged()
{
  this->setText(m_text->GetText().c_str());
  //this->update(); //No need to
}
