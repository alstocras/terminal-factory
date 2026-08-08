#include <iostream>
#include <ncurses.h>
#include <vector>

// main function
int main() {
  // ncurses screen stuff
  initscr();

  // colours
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);

  // activate 1
  attron(COLOR_PAIR(1));

  // drawing hello world
  mvwprintw(stdscr, 2, 2, "hello there");

  // activate 2
  attron(COLOR_PAIR(2));

  // drawing another thing
  mvwprintw(stdscr, 10, 10, "me too");

  // reload
  refresh();
}
