#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbaboutdialog.h"

#include <cassert>

#include <QLabel>
#include <QLayout>
#include <QPixmap>

#include "about.h"
#include "pvdbmenudialog.h"
#include "qtarrowitem.h"
#include "qthideandshowdialog.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::QtAboutDialog> ribi::pvdb::QtPvdbAboutDialog::Get()
{
  About about = pvdb::MenuDialog().GetAbout();
  about.AddLibrary("QtArrowItem version: " + QtArrowItem::GetVersion());
  about.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  about.AddLibrary("QtQuadBezierArrowItem version: " + QtQuadBezierArrowItem::GetVersion());
  about.AddLibrary("QtScopedDisable version: " + QtScopedDisable<int>::GetVersion());
  about.AddLibrary("Artwork from LibreOffice");
  const boost::shared_ptr<QtAboutDialog> d(new QtAboutDialog(about));
  assert(d);

  //Add Loom image
  assert(d->layout());
  QLabel * const label = new QLabel(d.get());
  label->setPixmap(QPixmap(":/images/PicLoomAbout.png"));
  d->layout()->addWidget(label);
  return d;
}
