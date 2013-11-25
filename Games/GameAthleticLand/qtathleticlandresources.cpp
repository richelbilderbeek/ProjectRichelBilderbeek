#include "qtathleticlandresources.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include <QFile>

#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::athl::QtAthleticLandResources::QtAthleticLandResources()
  : m_background(QPixmap(GetBackgroundFilename().c_str())),
    m_player{}
{
  //No need to check for member variables, as all pixmaps are checked here
  for (const std::string& filename: GetAllFilenames())
  {
    if (!fileio::IsRegularFile(filename))
    {
      const std::string qtfilename {
        GetQtResourcesBasename()
        + std::string("/")
        + filename
      };
      TRACE(qtfilename);
      QFile file(qtfilename.c_str());
      file.copy(filename.c_str());
    }
    if (!fileio::IsRegularFile(filename))
    {
      TRACE("ERROR");
      TRACE(filename);
    }
    assert(fileio::IsRegularFile(filename));
  }
}

const std::vector<std::string> ribi::athl::QtAthleticLandResources::GetAllFilenames() const noexcept
{
  return {
    GetBackgroundFilename(),
    GetPlayerFilename()
  };
}

const QPixmap& ribi::athl::QtAthleticLandResources::GetPlayer(const State state) const noexcept
{
  assert(m_player.find(state) != m_player.end());
  return (*m_player.find(state)).second;
}
