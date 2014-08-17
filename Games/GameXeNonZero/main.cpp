#include <string>
#include <iostream>
#include <cassert>

#include "xenonzeromaindialog.h"

int main()
{

  ribi::xnz::Dialog s;

  while(!s.IsGameOver())
  {
    std::cout << s << std::endl;
    //s.AskUserInputAndProcess();
    //s.DrawSprites();
  }

  std::cout << "GAME OVER!" << std::endl;
  std::cout << "Press any key to quit." << std::endl;
  std::string temp;
  std::getline(std::cin,temp);
}
