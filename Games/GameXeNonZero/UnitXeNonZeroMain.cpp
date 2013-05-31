#include <string>
#include <iostream>
#include <Assert.hpp>

#include "UnitXeNonZero.h"



int main()
{

  XeNonZero s;

  while(s.IsGameOver()==false)
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
