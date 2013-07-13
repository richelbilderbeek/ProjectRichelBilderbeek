#ifndef VIRTUALBASTARD_H
#define VIRTUALBASTARD_H

#include <string>

///The VirtualBastard class
struct VirtualBastard
{
  VirtualBastard();


  ///Make the mouse cursor perform a click
  static void Click();

  ///Set the mouse cursor its current position
  static const std::pair<int,int> GetMousePos();

  ///Set the mouse cursor to a certain position
  static void SetMousePos(const int x, const int y);

  ///Press a key
  static void PressKey(const char key);

  ///Sleep for some time (in msecs)
  static void Sleep(const int m_secs);

  private:
  static void Execute(const std::string& cmd);
};

#endif // VIRTUALBASTARD_H
