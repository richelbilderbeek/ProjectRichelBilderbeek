//---------------------------------------------------------------------------
#ifndef WTSERVERPUSHERCLIENT_H
#define WTSERVERPUSHERCLIENT_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------

namespace ribi {

///WtServerPusherClient is a client responding to WtServerPusher
///and to be used as a base class
struct WtServerPusherClient
{
  virtual ~WtServerPusherClient();

  ///Get the version of this class
  static const std::string GetVersion();

  ///Get the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///OnServerPush is called when the WtServerPusher is posted to
  virtual void OnServerPush() = 0;

  protected:
  ///WtServerPusherClient constructor is protected
  ///because it is to be used as a base class
  WtServerPusherClient();

  private:
  ///Respond to the server
  void OnServer();
};

} //~namespace ribi

#endif // WTSERVERPUSHERCLIENT_H
