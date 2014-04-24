#include "qtathleticlandresources.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include <QFile>

#include "athleticlandplayerstates.h"
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
    if (!fileio::FileIo().IsRegularFile(filename))
    {
      const std::string qtfilename {
        GetQtResourcesBasename()
        + "/"
        + filename
      };
      TRACE(qtfilename);
      QFile file(qtfilename.c_str());
      file.copy(filename.c_str());
    }
    if (!fileio::FileIo().IsRegularFile(filename))
    {
      TRACE("ERROR");
      TRACE(filename);
    }
    assert(fileio::FileIo().IsRegularFile(filename));
  }
}

std::map<ribi::athl::PlayerState,QPixmap> ribi::athl::QtAthleticLandResources::CreatePlayer() const noexcept
{
  std::map<PlayerState,QPixmap> m;

  m.insert(std::make_pair(ribi::athl::PlayerState::stand_left,FetchPixmap(GetPlayerStandLeftFilename())));
  m.insert(std::make_pair(ribi::athl::PlayerState::stand_right,FetchPixmap(GetPlayerStandRightFilename())));

  return m;
}

QPixmap ribi::athl::QtAthleticLandResources::FetchPixmap(const std::string& filename) const noexcept
{
  const std::string qtfilename = GetQtResourcesBasename() + "/" + filename;
  const QPixmap pixmap(qtfilename.c_str());
  assert(pixmap.height() > 0);
  assert(pixmap.width() > 0);
  return pixmap;

}

std::vector<std::string> ribi::athl::QtAthleticLandResources::GetAllFilenames() const noexcept
{
  return {
    GetBackgroundFilename(),
    GetPlayerStandLeftFilename(),
    GetPlayerStandRightFilename()
  };
}

const QPixmap& ribi::athl::QtAthleticLandResources::GetPlayer(const PlayerState state) const noexcept
{
  #ifndef NDEBUG
  if(m_player.find(state) == m_player.end())
  {
    TRACE(PlayerStates().ToStr(state));
  }
  #endif
  assert(m_player.find(state) != m_player.end());
  return (*m_player.find(state)).second;
}
