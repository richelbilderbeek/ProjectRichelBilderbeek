#ifndef QTMYITEM_H
#define QTMYITEM_H

#include <QStandardItem>

struct QtMyItem : public QStandardItem
{
  QtMyItem(const QString &text);
};

#endif // QTMYITEM_H
