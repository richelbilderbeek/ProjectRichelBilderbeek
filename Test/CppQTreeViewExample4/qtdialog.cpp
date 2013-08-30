#include "qtdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QStandardItemModel>
#include <QDirModel>


#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  QDirModel * const model = new QDirModel;
  model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

  QTreeView * const view = ui->treeView;
  view->setModel(model);
  view->header()->setSortIndicator(0, Qt::AscendingOrder);
  view->header()->setSortIndicatorShown(true);
  //view->header()->setClickable(true);

  const QModelIndex index = model->index(QDir::currentPath());
  view->expand(index);
  view->scrollTo(index);
  view->setCurrentIndex(index);
  view->resizeColumnToContents(0);

}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); return; }
}
