#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
//#include <Wt/WLineEdit>
#include <Wt/WPushButton>
//#include <Wt/WText>
#include <Wt/WServer>

struct ApplicationCppValgrindExample6 : public Wt::WApplication
{
  ApplicationCppValgrindExample6(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("CppValgrindExample6");
    {
      Wt::WPushButton * button = new Wt::WPushButton("Call std::exit(0)");
      button->clicked().connect(this,&ApplicationCppValgrindExample6::DoExit);
      this->root()->addWidget(button);
    }
    {
      Wt::WPushButton * button = new Wt::WPushButton("Call Wt::WServer::waitForShutdown and Wt::WServer::stop");
      button->setEnabled(false);
      button->clicked().connect(this,&ApplicationCppValgrindExample6::DoStop1);
      this->root()->addWidget(button);
    }
    {
      Wt::WPushButton * button = new Wt::WPushButton("Call Wt::WServer::stop");
      button->setEnabled(false);
      button->clicked().connect(this,&ApplicationCppValgrindExample6::DoStop2);
      this->root()->addWidget(button);
    }
    {
      Wt::WPushButton * button = new Wt::WPushButton("Throw");
      button->clicked().connect(this,&ApplicationCppValgrindExample6::DoThrow);
      this->root()->addWidget(button);
    }
  }

  void DoExit() { std::exit(0); }
  void DoStop1()
  {
    Wt::WServer::instance()->waitForShutdown();
    Wt::WServer::instance()->stop();
  }
  void DoStop2() { Wt::WServer::instance()->stop(); }
  void DoThrow() { throw; }
};


Wt::WApplication * CreateApplication(const Wt::WEnvironment& env)
{
  return new ApplicationCppValgrindExample6(env);
}

int main(int, char *argv[])
{
  //C++0x initializer list
  const char * const v[7] =
  {
    argv[0],
    "--docroot", ".",
    "--http-port", "8080",
    "--http-address", "0.0.0.0"
  };
  return WRun(7, const_cast<char**>(v), &CreateApplication);
}
