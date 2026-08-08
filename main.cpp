#include <ncurses.h>

// main function
int main() {
  // ncurses screen stuff
  initscr();
  cbreak();
  noecho();

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

  // refresh
  refresh();

  // turn off colours
  attroff(COLOR_PAIR(1));

  // keypress check
  int ch;
  while ((ch = getch()) != 'q') {
    // game loop
  }

  // exit
  endwin();

  // return
  return 0;
}
