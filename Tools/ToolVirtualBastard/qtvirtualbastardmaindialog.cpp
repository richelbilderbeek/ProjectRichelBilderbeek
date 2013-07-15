#include "qtvirtualbastardmaindialog.h"

#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include "virtualbastard.h"

#include "ui_qtvirtualbastardmaindialog.h"

extern "C"
{
  #include "libcvautomation/libcvautomation.h"
}

QtVirtualBastardMainDialog::QtVirtualBastardMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtVirtualBastardMainDialog)
{
  ui->setupUi(this);
}

QtVirtualBastardMainDialog::~QtVirtualBastardMainDialog()
{
  delete ui;
}

void QtVirtualBastardMainDialog::on_button_clicked()
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

const std::vector<std::string> QtVirtualBastardMainDialog::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

void QtVirtualBastardMainDialog::on_button_set_mouse_pos_clicked()
{
  VirtualBastard::SetMousePos(ui->box_x->value(),ui->box_y->value());
}

void QtVirtualBastardMainDialog::on_button_click_clicked()
{
  VirtualBastard::Click();
  VirtualBastard::Click();
  VirtualBastard::Click();
  VirtualBastard::Click();
}

void QtVirtualBastardMainDialog::on_button_get_pos_clicked()
{
  const std::pair<int,int> pos = VirtualBastard::GetMousePos();
  const std::string text
    = "("
    + boost::lexical_cast<std::string>(pos.first)
    + ","
    + boost::lexical_cast<std::string>(pos.second)
    + ")";
  ui->label_pos->setText(text.c_str());

}
