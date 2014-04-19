#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/program_options.hpp>
#include <boost/signals2.hpp>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPushButton>
#pragma GCC diagnostic pop

struct WtWidget : public Wt::WPaintedWidget
{
  WtWidget()
  {
    this->resize(32,32);
  }
  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice)
  {
    Wt::WPainter painter(paintDevice);
    for (int y=0; y!=32; ++y)
    {
      for (int x=0; x!=32; ++x)
      {
        painter.setPen(
          Wt::WPen(
            Wt::WColor(
              ((x+0) * 8) % 256,
              ((y+0) * 8) % 256,
              ((x+y) * 8) % 256)));
        //Draw a line of one pixel long
        painter.drawLine(x,y,x+1,y);
        //drawPoint yiels too white results
        //painter.drawPoint(x,y);
      }
    }
  }
};

struct WtDialog : public Wt::WContainerWidget
{
  WtDialog()
  : m_widget(new WtWidget)
  {
    this->addWidget(m_widget);
  }
  private:
  WtWidget * const m_widget;
};

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new WtDialog)
  {
    this->setTitle("Thinking Wt 2: creating a  widget");
    root()->addWidget(m_dialog);
  }
  private:
  WtDialog * const m_dialog;
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  // Declare the supported options.
  boost::program_options::options_description d(
    "Allowed options for CppWtAutoRun");
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
