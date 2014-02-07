//Code adapted from http://invisible-island.net/ncurses/ncurses-intro.html

#include <cassert>
#include <cstdlib>
#include <csignal>

#include "curses.h"

static void finish(int sig);

int main()
{
  std::signal(SIGINT, finish);
  initscr();
  keypad(stdscr, TRUE);
  cbreak();

  int x = 0;
  int y = 0;

  while (1)
  {
    move(y,x);
    refresh();
    const int c = getch();
    switch (c)
    {
      case KEY_UP   : y-=(y-1>   0  ? 1 : 0); break;
      case KEY_RIGHT: x+=(x+1<COLS  ? 1 : 0); break;
      case KEY_DOWN : y+=(y+1<LINES ? 1 : 0); break;
      case KEY_LEFT : x-=(x-1>   0  ? 1 : 0); break;
      default: addch(c); x+=(x+1<COLS  ? 1 : 0); break;
    }
  }
  finish(0);
}

static void finish(int sig)
{
  endwin();
  std::exit(sig);
}
