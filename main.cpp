#include <ncurses.h>
#include <string>

// main function
int main() {
  // ncurses screen stuff
  initscr();
  curs_set(0);
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

  // set positon
  int pos[2] = {centre[0], centre[1]};
  char *icon = ">";

  // turn on player colour
  attron(COLOR_PAIR(1));

  // print character
  mvwprintw(stdscr, centre[0], centre[1], icon);

  // refresh
  refresh();

  // turn off colours
  attroff(COLOR_PAIR(1));

  // keypress check
  int ch;
  while ((ch = getch()) != 'q') {
    // game loop

    // clear all text
    erase();

    // movement!!
    if ((ch = getch()) == 'y') {
      pos[0] -= 1;
      icon = "^";
    }

    // render and refresh
    attron(COLOR_PAIR(1));
    mvwprintw(stdscr, pos[0], pos[1], icon);
    refresh();
    attroff(COLOR_PAIR(1));
  }

  // exit
  endwin();

  // return
  return 0;
}
