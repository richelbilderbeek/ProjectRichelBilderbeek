#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdboverviewdialog.h"

#include <QKeyEvent>
#include <QVBoxLayout>

#include "qtpvdboverviewwidget.h"
#include "trace.h"

QtPvdbOverviewDialog::QtPvdbOverviewDialog(QWidget* parent)
  : QtHideAndShowDialog(parent)
{
  
  QLayout * const layout = new QVBoxLayout(this);
  this->setLayout(layout);
  QtPvdbOverviewWidget * const widget = new QtPvdbOverviewWidget;
  layout->addWidget(widget);
}

void QtPvdbOverviewDialog::keyPressEvent(QKeyEvent* e)
{
  assert(e);
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(e);
}
