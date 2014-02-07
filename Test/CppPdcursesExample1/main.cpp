//Code adapted from http://invisible-island.net/ncurses/ncurses-intro.html

#include <cassert>
#include <cstdlib>
#include <csignal>

#include "curses.h"

static void finish(int sig);

int main()
{
  int num = 0;

  /* initialize your non-curses data structures here */

  std::signal(SIGINT, finish);      /* arrange interrupts to terminate */
  initscr();      /* initialize the curses library */
  keypad(stdscr, TRUE);  /* enable keyboard mapping */
  cbreak();       /* take input chars one at a time, no wait for \n */
  echo();         /* echo input - in color */

  if (has_colors())
  {
    start_color();

    /*
    * Simple color assignment, often all we need.  Color pair 0 cannot
    * be redefined.  This example uses the same value for the color
    * pair as for the foreground color, though of course that is not
    * necessary:
    */
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_CYAN,    COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
  }

  for (;;)
  {
    int c = getch();     /* refresh, accept single keystroke of input */
    attrset(COLOR_PAIR(num % 8));
    num++;

    /* process the command keystroke */
    if (c == KEY_DOWN) finish(0);
  }

  finish(0);               /* we're done */
}

static void finish(int sig)
{
  endwin();

  /* do your non-curses wrapup here */

  std::exit(sig);
}
