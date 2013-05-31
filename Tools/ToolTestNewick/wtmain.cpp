//---------------------------------------------------------------------------
#include <boost/program_options.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
//---------------------------------------------------------------------------
#include "encranger.h"
#include "wttestnewickdialog.h"
#include "wtaboutdialog.h"
//---------------------------------------------------------------------------
struct WtTestNewickApplication : public Wt::WApplication
{
  WtTestNewickApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->useStyleSheet("wt.css");
    this->setTitle("TestNewick");
    ShowMain();
  }
  void ShowMain()
  {
    WtTestNewickDialog * const d
      = new WtTestNewickDialog;

    d->m_signal_about.connect(
      boost::bind(
      &WtTestNewickApplication::ShowAbout,
      this));

    root()->clear();
    root()->addWidget(d);

  }
  void ShowAbout()
  {
    About about = TestNewickDialog::GetAbout();
    about.AddLibrary("Encranger: version " + Encranger::GetVersion());

    WtAboutDialog * const d
      = new WtAboutDialog(
        about);

    d->m_signal_close.connect(
      boost::bind(
      &WtTestNewickApplication::ShowMain,
      this));

    root()->clear();
    root()->addWidget(d);

  }
};
//---------------------------------------------------------------------------
Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtTestNewickApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  boost::program_options::options_description d(
    "Allowed options for TestNewick");
  std::string docroot;
  std::string http_address;
  std::string http_port;
  d.add_options()
      ("help",
        "produce this help message")
      ("docroot",
         boost::program_options::value<std::string>(&docroot)->default_value("."),
         "the docroot")
      ("http-address",
         boost::program_options::value<std::string>(&http_address)->default_value("0.0.0.0"),
         "the server's http address")
      ("http-port",
         boost::program_options::value<std::string>(&http_port)->default_value("8080"),
         "the server's http port")
      ;

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
    return 0;
  }

  //Create the arguments in std::string format
  std::vector<std::string> v(7);
  v[0] = argv[0];
  v[1] = "--docroot";
  v[2] = docroot;
  v[3] = "--http-address";
  v[4] = http_address;
  v[5] = "--http-port";
  v[6] = http_port;

  //Convert the arguments to char* format
  std::vector<char*> w(7);
  for (int i=0; i!=7; ++i) w[i] = &v[i][0];

  //Give Wt the modified parameters
  return WRun(w.size(), &w[0], &createApplication);
}
//---------------------------------------------------------------------------
