#ifndef QTTREE_H
#define QTTREE_H

#include <QWidget>

namespace Ui {
class QtTree;
}

class QtTree : public QWidget
{
  Q_OBJECT

public:
  explicit QtTree(QWidget *parent = 0);
  ~QtTree();

private:
  Ui::QtTree *ui;
};

#endif // QTTREE_H
