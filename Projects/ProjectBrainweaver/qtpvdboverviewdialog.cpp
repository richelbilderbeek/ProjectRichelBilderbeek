#include "qtpvdboverviewdialog.h"

#include <QKeyEvent>
#include <QVBoxLayout>

#include "qtpvdboverviewwidget.h"
#include "trace.h"

ribi::pvdb::QtPvdbOverviewDialog::QtPvdbOverviewDialog(QWidget* parent)
  : QtHideAndShowDialog(parent)
{
  
  QLayout * const layout = new QVBoxLayout(this);
  this->setLayout(layout);
  QtPvdbOverviewWidget * const widget = new QtPvdbOverviewWidget;
  layout->addWidget(widget);
}

void ribi::pvdb::QtPvdbOverviewDialog::keyPressEvent(QKeyEvent* e)
{
  assert(e);
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(e);
}
