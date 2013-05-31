//---------------------------------------------------------------------------
#ifndef WTBROADCASTSERVERCLIENT_H
#define WTBROADCASTSERVERCLIENT_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
///WtBroadcastServerClient is a client responding to WtBroadcastServer
///and to be used as a base class
struct WtBroadcastServerClient
{
  virtual ~WtBroadcastServerClient();

  ///Get the version of this class
  static const std::string GetVersion();

  ///Get the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///UpdatePage is called when the WtBroadcastServer triggers an update by timer
  virtual void UpdatePage() = 0;

  protected:
  ///WtBroadcastServerClient constructor is protected
  ///because it is to be used as a base class
  WtBroadcastServerClient();

  private:
  ///Respond to the server
  void OnServer();
};
//---------------------------------------------------------------------------
#endif // WTBROADCASTSERVERCLIENT_H
