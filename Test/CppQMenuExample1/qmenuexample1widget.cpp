#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qmenuexample1widget.h"

#include <QMenu>
#pragma GCC diagnostic pop


QMenuExample1Widget::QMenuExample1Widget(QWidget *parent)
  : QWidget(parent)
{
  ///Too bad, does not work :-(
  setContextMenuPolicy(Qt::CustomContextMenu);
  QObject::connect(this,SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(ShowPopUpMenu(const QPoint&)));
}

void QMenuExample1Widget::OnClickPopUpMenu()
{
  this->setWindowTitle("Clicked");
}

void QMenuExample1Widget::OnShowPopUpMenu(const QPoint& pos)
{
  QMenu * const menu = new QMenu;
  menu->addAction(tr("Test Item"), this, SLOT(OnClickPopUpMenu()));

  menu->exec(this->mapToGlobal(pos));
}
