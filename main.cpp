#include <iostream>
#include <ncurses.h>
#include <vector>

// main function
int main() {
  // ncurses screen stuff
  initscr();

  // colours!!
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);

  // get centre
  int y, x;
  getmaxyx(stdscr, y, x);

  // divide by 2
  y = y * 0.5;
  x = x * 0.5;

  // the ncurses convention is y/x not x/y soooo
  int centre[2] = {y, x};

  // turn on player colour
  attron(COLOR_PAIR(1));

  // print character
  mvwprintw(stdscr, centre[0], centre[1], ">");

  // turn off colours
  attroff(COLOR_PAIR(1));

  // dont close until keypress
  getch();

  // close and clean
  endwin();

  // its an int function
  return 0;
}
