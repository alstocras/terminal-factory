#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

// main function
int main() {
  // seed random gen
  srand(time(0));

  // ncurses screen stuff
  initscr();
  curs_set(0);
  cbreak();
  noecho();

  // colours!!
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);

  // get centre
  int y, x;
  getmaxyx(stdscr, y, x);

  // map
  vector<vector<int>> map;

  // fill up map with 0s
  for (int yi = 0; yi < y; yi++) {
    vector<int> temp;
    for (int xi = 0; xi < x; xi++) {
      temp.push_back(0);
    }
    map.push_back(temp);
  }

  // terrain gen
  for (int yb = 0; yb < map.size(); yb++) {
    for (int xb = 0; xb < map[yb].size(); xb++) {
      int randomNum = rand() % 100;
      cout << randomNum;

      if (randomNum >= 50) {
        map[yb][xb] = 2;
      } else {
        map[yb][xb] = 0;
      }
    }
  }

  // divide by 2
  y = y * 0.5;
  x = x * 0.5;

  // the ncurses convention is y/x not x/y soooo
  int centre[2] = {y, x};

  // set positon
  int pos[2] = {centre[0], centre[1]};

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

    // erase player
    mvwprintw(stdscr, pos[0], pos[1], " ");
    refresh();

    // movement!! (very janky ik)
    if ((ch = getch()) == 'y') {
      pos[0] -= 1;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "^");
      refresh();
      attroff(COLOR_PAIR(1));
    } else if ((ch = getch()) == 'i') {
      pos[0] += 1;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "v");
      refresh();
      attroff(COLOR_PAIR(1));
    } else if ((ch = getch()) == 'c') {
      pos[1] -= 3;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "<");
      refresh();
      attroff(COLOR_PAIR(1));
    } else if ((ch = getch()) == 'e') {
      pos[1] += 3;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], ">");
      refresh();
      attroff(COLOR_PAIR(1));
    }

    // drill placement check
    if ((ch = getch()) == ' ') {
      map[pos[0]][pos[1]] = 1;
    }

    // drawing map
    for (int ya = 0; ya < map.size(); ya++) {
      for (int xa = 0; xa < map[ya].size(); xa++) {

        if (map[ya][xa] == 1) {
          // render and refresh
          attron(COLOR_PAIR(2));
          mvwprintw(stdscr, ya, xa, "*");
          refresh();
          attroff(COLOR_PAIR(2));
        } else if (map[ya][xa] == 2) {
          // render and refresh
          attron(COLOR_PAIR(3));
          mvwprintw(stdscr, ya, xa, "0");
          refresh();
          attroff(COLOR_PAIR(3));
        } else {
          mvwprintw(stdscr, ya, xa, " ");
        }
      }
    }
  }

  // exit
  endwin();

  // return
  return 0;
}
