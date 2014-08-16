#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>

#include "fileio.h"
#include "qtconnectthreeresources.h"
#include "qtconnectthreemenudialog.h"
#include "trace.h"

#include <QFile>
#include <QIcon>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  START_TRACE();

  ribi::con3::QtConnectThreeMenuDialog w;
  {
    ribi::con3::QtConnectThreeResources resources;
    const std::string icon_filename = resources.GetIconFilename();
    assert(ribi::fileio::FileIo().IsRegularFile(icon_filename.c_str()));
    w.setWindowIcon(QIcon(QPixmap(icon_filename.c_str())));
  }
  w.show();
  return a.exec();
}
