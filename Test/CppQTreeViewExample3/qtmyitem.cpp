#include "qtmyitem.h"

QtMyItem::QtMyItem(const QString &text)
  : QStandardItem(text)
{
  this->setEditable(true);
  this->setDragEnabled(true);
  this->setDropEnabled(true);
}
