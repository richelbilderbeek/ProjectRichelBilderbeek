#include <string>
#include <iostream>
#include <cassert>

#include "xenonzerodialog.h"

int main()
{

  xenon_zero::XeNonZero s;

  while(!s.IsGameOver())
  {
    std::cout << s << std::endl;
    s.AskUserInputAndProcess();
    s.DrawSprites();
  }

  std::cout << "GAME OVER!" << std::endl;
  std::cout << "Press any key to quit." << std::endl;
  std::string temp;
  std::getline(std::cin,temp);
}
