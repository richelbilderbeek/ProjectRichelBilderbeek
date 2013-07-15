#include "virtualbastard.h"

#include <chrono>
#include <limits>
//#include <sstream>
#include <thread>

#include <boost/lexical_cast.hpp>

extern "C"
{
  #include "libcvautomation/libcvautomation.h"
}

VirtualBastard::VirtualBastard()
{
  XInitThreads();
}

void VirtualBastard::Click()
{
  const std::string cmd = "mouseclick";
  Execute(cmd);
}


void VirtualBastard::Execute(const std::string& cmd)
{
  //Open a display (whatever that may be)
  const std::string display_name = "";
  Display * const display = XOpenDisplay( display_name.c_str() );
  assert(display);

  //Convert the line (with the command) to a C style string
  char * const command = new char[ cmd.size() + 1 ];
  strcpy(command,&cmd[0]);

  //Run the command
  /*const cvaPoint p =*/ xte_commandString(display,command,1,0,std::numeric_limits<int>().max(),1);

  //Close the display (whatever that may be)
  XCloseDisplay( display );

  //Don't forget to delete a C-style string :-(
  delete[] command;

  //Give some feedback
  /*
  std::stringstream s;
  s << "Execute command: '" << cmd << "': ";
  if (p.x == -2 && p.y == -2)
  {
    s << "OK";
  }
  else
  {
    s << "(" << p.x << "," << p.y << ")";
  }
  */
}

const std::pair<int,int> VirtualBastard::GetMousePos()
{
  //Open a display (whatever that may be)
  const std::string display_name = "";
  Display * const display = XOpenDisplay( display_name.c_str() );
  assert(display);
  const cvaPoint p = xte_mouseLocation(display);
  return std::make_pair(p.x,p.y);
}

void VirtualBastard::PressKey(const char /* key */)
{

}

void VirtualBastard::SetMousePos(const int x, const int y)
{
  const std::string cmd
    = "mousexy "
    + boost::lexical_cast<std::string>(x)
    + " "
    + boost::lexical_cast<std::string>(y);
  Execute(cmd);
}

void VirtualBastard::Sleep(const int m_secs)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(m_secs));
}
