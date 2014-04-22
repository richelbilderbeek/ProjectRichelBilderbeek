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
  const QPixmap& GetPlayer(const State state) const noexcept;

  private:

  const QPixmap m_background;
  const std::map<State,QPixmap> m_player;

  std::vector<std::string> GetAllFilenames() const noexcept;
  std::string GetBackgroundFilename() const noexcept { return "Background1.png"; }
  std::string GetPlayerFilename() const noexcept { return "MainCharStandRight.png"; }
  std::string GetQtResourcesBasename() const noexcept { return ":/GameAthleticLand/images"; }
};

} //~namespace ribi
} //~namespace athl

#endif // QTATHLETICLANDRESOURCES_H
