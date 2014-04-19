#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
//---------------------------------------------------------------------------
#include "wtautoconfig.h"
//---------------------------------------------------------------------------
const std::string GetIpAddress(const Wt::WEnvironment& env)
{
  return env.clientAddress();
}
//---------------------------------------------------------------------------
struct WtDialog : public Wt::WContainerWidget
{
  WtDialog(const std::string& ip_address)
  {
    new Wt::WLabel(
      std::string("Client IP address: ")
      + ip_address,this);
  }
};
//---------------------------------------------------------------------------
struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {

    this->setTitle("CppWtGetIpAddress");
    this->useStyleSheet("wt.css");
    this->enableUpdates();
    const std::string ip_address = env.clientAddress();
    root()->addWidget(new WtDialog(ip_address));
  }
};
//---------------------------------------------------------------------------
Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  WtAutoConfig a(argc,argv,createApplication);
  WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}
//---------------------------------------------------------------------------
