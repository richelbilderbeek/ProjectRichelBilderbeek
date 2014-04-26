#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "wtautoconfig.h"
#include "wtconnectthreemenudialog.h"
#include "connectthreeresources.h"

#include <cassert>

struct WtConnectThreeApplication : public Wt::WApplication
{
  WtConnectThreeApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("ConnectThree");
    this->useStyleSheet("wt.css");
<<<<<<< HEAD
<<<<<<< HEAD
    root()->addWidget(new ribi::con3::WtConnectThreeMenuDialog);
=======
    root()->addWidget(new ribi::WtConnectThreeMenuDialog);
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
=======
    root()->addWidget(new ribi::WtConnectThreeMenuDialog);
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
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


