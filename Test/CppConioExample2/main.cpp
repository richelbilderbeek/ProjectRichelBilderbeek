#include <conio.h>

int main()
{
  _gotoxy(10, 10); //Does not compile
  _textcolor(YELLOW); //Does not compile
  _textbackground(BLUE); //Does not compile
  _cputs("Hello");
}
