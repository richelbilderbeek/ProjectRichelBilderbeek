#include <cassert>
#include <cstdlib>
#include <csignal>
#include <iostream>
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
      case KEY_SHIFT_L:
      case KEY_SHIFT_R:
      case KEY_CONTROL_L:
      case KEY_CONTROL_R:
      case KEY_ALT_L:
      case KEY_ALT_R:
        break;
      case KEY_UP   : y-=(y-1>   0  ? 1 : 0); break;
      case KEY_RIGHT: x+=(x+1<COLS  ? 1 : 0); break;
      case KEY_DOWN : y+=(y+1<LINES ? 1 : 0); break;
      case KEY_LEFT : x-=(x-1>   0  ? 1 : 0); break;
      case 8: case KEY_BACKSPACE: x-=(x-1>0 ? 1 : 0); move(y,x); addch(' '); break;
      case KEY_EXIT: finish(0);
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
