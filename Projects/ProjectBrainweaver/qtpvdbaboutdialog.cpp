#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbaboutdialog.h"

#include <cassert>

#include "about.h"
#include "pvdbmenudialog.h"
#include "qtarrowitem.h"
#include "qthideandshowdialog.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"

const boost::shared_ptr<QtAboutDialog> QtPvdbAboutDialog::Get()
{
  About about = pvdb::MenuDialog::GetAbout();
  about.AddLibrary("QtArrowItem version: " + QtArrowItem::GetVersion());
  about.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  about.AddLibrary("QtQuadBezierArrowItem version: " + QtQuadBezierArrowItem::GetVersion());
  about.AddLibrary("QtScopedDisable version: " + QtScopedDisable<int>::GetVersion());
  const boost::shared_ptr<QtAboutDialog> d(new QtAboutDialog(about));
  assert(d);
  return d;
}
