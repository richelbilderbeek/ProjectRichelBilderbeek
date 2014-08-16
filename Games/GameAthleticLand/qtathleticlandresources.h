#ifndef QTATHLETICLANDRESOURCES_H
#define QTATHLETICLANDRESOURCES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <map>
#include <QPixmap>
#include "athleticlandplayerstate.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace athl {

struct QtAthleticLandResources
{
  QtAthleticLandResources();
  const QPixmap& GetBackground() const noexcept { return m_background; }
  const QPixmap& GetPlayer(const PlayerState state) const noexcept;

  private:

  const QPixmap m_background;
  const std::map<PlayerState,QPixmap> m_player;

  std::map<PlayerState,QPixmap> CreatePlayer() const noexcept;
  std::vector<std::string> GetAllFilenames() const noexcept;

  ///Tries to obtain a pixmap from the resources from a filename
  ///For example, when called with 'PlayerStandLeft.png',
  ///it might try to load ':/AthleticLand/images/PlayerStandLeft.png'
  ///and create a QPixmap from it.
  ///Will terminate if pixmap is not found
  QPixmap FetchPixmap(const std::string& filename) const noexcept;

  std::string GetBackgroundFilename() const noexcept { return "Background1.png"; }
  std::string GetPlayerStandLeftFilename() const noexcept { return "MainCharStandLeft.png"; }
  std::string GetPlayerStandRightFilename() const noexcept { return "MainCharStandRight.png"; }
  std::string GetQtResourcesBasename() const noexcept { return ":/GameAthleticLand/images"; }
};

} //~namespace ribi
} //~namespace athl

#endif // QTATHLETICLANDRESOURCES_H
