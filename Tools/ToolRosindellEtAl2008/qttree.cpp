#include "qttree.h"
#include "ui_qttree.h"

QtTree::QtTree(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtTree)
{
  ui->setupUi(this);
}

QtTree::~QtTree()
{
  delete ui;
}
