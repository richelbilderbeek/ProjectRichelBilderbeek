#include "qtdialog.h"

#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include "ui_qtdialog.h"

//#include <X11/keysymdef.h> //To find keymap

extern "C"
{
  #include "libcvautomation/libcvautomation.h"
}

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  #ifdef OLD_SKOOL_APPROACH_THAT_WORKS
  const std::string display_location = "";
  Display * const display = XOpenDisplay( display_location.c_str() );
  assert(display);
  const std::string command_str = "mousexy 100 100";
  char * const command = new char[ command_str.size() + 1 ];
  strcpy(command,&command_str[0]);
  xte_commandString(display,command,1,0,std::numeric_limits<int>().max(),1);
  XCloseDisplay( display );
  delete[] command;
  #endif

  ui->output->clear();
  const std::string text = ui->input->toPlainText().toStdString();
  const std::vector<std::string> lines = SeperateString(text,'\n');
  for (const std::string& line: lines)
  {
    //Open a display (whatever that may be)
    const std::string display_location = "";
    Display * const display = XOpenDisplay( display_location.c_str() );
    assert(display);

    //Convert the line (with the command) to a C style string
    char * const command = new char[ line.size() + 1 ];
    strcpy(command,&line[0]);

    //Run the command
    const cvaPoint p = xte_commandString(display,command,1,0,std::numeric_limits<int>().max(),1);

    //Close the display (whatever that may be)
    XCloseDisplay( display );

    //Don't forget to delete a C-style string :-(
    delete[] command;

    //Give some feedback
    std::stringstream s;
    s << "Execute command: '" << line << "': ";
    if (p.x == -2 && p.y == -2)
    {
      s << "OK";
    }
    else
    {
      s << "(" << p.x << "," << p.y << ")";
    }
    ui->output->appendPlainText(s.str().c_str());
  }
  //Show the display again, when a mouseclick has caused it to hide
  this->hide();
  this->show();
}

const std::vector<std::string> QtDialog::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}
