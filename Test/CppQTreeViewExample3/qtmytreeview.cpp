#include "qtmytreeview.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragMoveEvent>

QtMyTreeView::QtMyTreeView(QWidget * const parent)
  : QTreeView(parent)
{
  this->setAcceptDrops(true);
  this->setAlternatingRowColors(true);
  this->setAnimated(true);
  this->setDragDropMode(QAbstractItemView::InternalMove);
  this->setDragEnabled(true);
  this->setDropIndicatorShown(true);
  this->setExpandsOnDoubleClick(true);
  this->setHeaderHidden(true);
  this->setItemsExpandable(true);
  this->setSelectionMode(QAbstractItemView::SingleSelection);
  this->setWordWrap(true);
}
