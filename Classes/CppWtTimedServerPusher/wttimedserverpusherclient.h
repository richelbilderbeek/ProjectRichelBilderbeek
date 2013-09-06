//---------------------------------------------------------------------------
#ifndef WTTIMEDSERVERPUSHERCLIENT_H
#define WTTIMEDSERVERPUSHERCLIENT_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>

namespace ribi {

///WtTimedServerPusherClient is a client responding to WtTimedServerPusher
///and to be used as a base class
struct WtTimedServerPusherClient
{
  virtual ~WtTimedServerPusherClient();

  ///Get the version of this class
  static const std::string GetVersion();

  ///Get the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///UpdatePage is called when the WtTimedServerPusher triggers an update by timer
  virtual void OnTimedServerPush() = 0;

  protected:
  ///WtTimedServerPusherClient constructor is protected
  ///because it is to be used as a base class
  WtTimedServerPusherClient();

  private:
  ///Respond to the server
  void OnServer();
};

} //~namespace ribi

#endif // WTTIMEDSERVERPUSHERCLIENT_H
