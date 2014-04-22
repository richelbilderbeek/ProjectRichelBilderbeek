#ifndef QTK3OPEENRIJRESOURCES_H
#define QTK3OPEENRIJRESOURCES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tribool.h"
#include "connectthreeresources.h"
#pragma GCC diagnostic pop

namespace ribi {

///QtK3OpEenRijResources is a class containing
///all filenames to be used by the program
///Its base class, ConnectThreeResources,
///ensures the files needed are present upon construction.
struct QtK3OpEenRijResources
  : public ::ribi::con3::ConnectThreeResources
{
  QtK3OpEenRijResources(const Tribool is_player3_kathleen = Tribool::Indeterminate);

  private:
  std::vector<std::string> CreatePlayerNames(const Tribool is_player3_kathleen);
  std::vector<std::string> CreatePlayerGreyNames(const Tribool is_player3_kathleen);
};

} //~namespace ribi

#endif // QTK3OPEENRIJRESOURCES_H
