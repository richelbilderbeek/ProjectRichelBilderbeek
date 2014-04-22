#include <conio.h>

int main()
{
  _cputs("conio example 1\nPress any key to quit\n");
  while (!kbhit()) { ; }
}
