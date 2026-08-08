#include <iostream>
#include <ncurses.h>
#include <vector>

// main function
int main() {
  // ncurses
  initscr();

  // drawing hello world
  mvwprintw(stdscr, 2, 2, "hello there");
  refresh();
}
