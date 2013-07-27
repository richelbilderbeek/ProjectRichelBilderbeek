#ifndef MYMODEL_H
#define MYMODEL_H

//#include <QAbstractTableModel>
#include <QStandardItemModel>

struct MyModel : public QStandardItemModel
{
public:
  MyModel(QObject *parent = 0);
  void AddRow();

private:
};

#endif // MYMODEL_H
