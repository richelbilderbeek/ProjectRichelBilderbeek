//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
//---------------------------------------------------------------------------
#include "chessboard.h"
#include "chesssquare.h"
#include "wtautoconfig.h"
//#include "wtchessboardwidget.h"
#include "trace.h"
//---------------------------------------------------------------------------
struct WtChessBoardDialog : public Wt::WContainerWidget
{
  WtChessBoardDialog()
  {
    //this->addWidget(new ribi::Chess::WtBoardWidget);
    this->addWidget(new Wt::WBreak);
    //this->addWidget(new ribi::Chess::WtKriegspielWidget);
  }
};
//---------------------------------------------------------------------------
struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("SearchAndDestroyChess");
    root()->addWidget(new WtChessBoardDialog);
  }
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  START_TRACE();
  ribi::WtAutoConfig a(argc,argv,createApplication);
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}

/*
  a.AddLibrary("WtServerPusher version: " + WtServerPusher::GetVersion());
  a.AddLibrary("WtServerPusherClient version: " + WtServerPusherClient::GetVersion());
  a.AddLibrary("WtTimedServerPusher version: " + WtTimedServerPusher::GetVersion());
  a.AddLibrary("WtTimedServerPusherClient version: " + WtTimedServerPusherClient::GetVersion());
*/
