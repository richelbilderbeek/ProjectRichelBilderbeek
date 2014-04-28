#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <cassert>

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "wtautoconfig.h"
#include "wtconnectthreemenudialog.h"
#include "connectthreeresources.h"
#pragma GCC diagnostic pop

struct WtConnectThreeApplication : public Wt::WApplication
{
  WtConnectThreeApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("ConnectThree");
    this->useStyleSheet("wt.css");
    root()->addWidget(new ribi::con3::WtConnectThreeMenuDialog);
  }
};

Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new WtConnectThreeApplication(env);
}

int main(int argc, char **argv)
{
  ribi::WtAutoConfig a(argc,argv,createApplication);
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}


