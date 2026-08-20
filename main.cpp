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

  // variables
  int extractSpeed = 0;
  float zeroes = 0;

  // ncurses screen stuff
  initscr();
  curs_set(0);
  cbreak();
  noecho();

  // colours!!
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);    // player
  init_pair(2, COLOR_YELLOW, COLOR_BLACK); // drills
  init_pair(3, COLOR_GREEN, COLOR_BLACK);  // ores
  init_pair(4, COLOR_BLACK, COLOR_RED);    // core
  init_pair(5, COLOR_BLACK, COLOR_CYAN);   // label

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
      int randomNum = rand() % 50;
      if (randomNum <= 25) {
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

  // place core
  map[centre[0]][centre[1]] = 3;

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

    // incrememnt resources
    zeroes += extractSpeed;

    // display 0s
    // const char *zStr = ("zeroes: " + to_string(zeroes)).c_str();
    attron(COLOR_PAIR(5));
    mvwprintw(stdscr, 0, 0, to_string(zeroes).c_str());
    refresh();
    attroff(COLOR_PAIR(5));

    // erase player
    mvwprintw(stdscr, pos[0], pos[1], " ");
    refresh();

    // movement!! (very janky ik)
    // up
    if ((ch = getch()) == 'y') {
      pos[0] -= 1;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "^");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    else if ((ch = getch()) == 'w') {
      pos[0] -= 1;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "^");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    // down
    else if ((ch = getch()) == 'i') {
      pos[0] += 1;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "v");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    else if ((ch = getch()) == 's') {
      pos[0] += 1;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "v");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    // left
    else if ((ch = getch()) == 'c') {
      pos[1] -= 3;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "<");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    else if ((ch = getch()) == 'a') {
      pos[1] -= 3;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], "<");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    // right
    else if ((ch = getch()) == 'e') {
      pos[1] += 3;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], ">");
      refresh();
      attroff(COLOR_PAIR(1));
    }
    else if ((ch = getch()) == 'd') {
      pos[1] += 3;

      // render and refresh
      attron(COLOR_PAIR(1));
      mvwprintw(stdscr, pos[0], pos[1], ">");
      refresh();
      attroff(COLOR_PAIR(1));
    }

    // drill placement check
    if ((ch = getch()) == ' ') {
      if (map[pos[0]][pos[1]] == 2) {
        extractSpeed += 1;
        map[pos[0]][pos[1]] = 1;
      }
    }

    // drawing map
    for (int ya = 0; ya < map.size(); ya++) {
      for (int xa = 0; xa < map[ya].size(); xa++) {

        // drills
        if (map[ya][xa] == 1) {
          // render and refresh
          attron(COLOR_PAIR(2));
          mvwprintw(stdscr, ya, xa, "*");
          refresh();
          attroff(COLOR_PAIR(2));
        }
        // ore
        else if (map[ya][xa] == 2) {
          // render and refresh
          attron(COLOR_PAIR(3));
          mvwprintw(stdscr, ya, xa, "0");
          refresh();
          attroff(COLOR_PAIR(3));
        }
        // core
        else if (map[ya][xa] == 3) {
          // render and refresh
          attron(COLOR_PAIR(4));
          mvwprintw(stdscr, ya, xa, "c");
          refresh();
          attroff(COLOR_PAIR(4));
        }
        // nothing
        else {
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
