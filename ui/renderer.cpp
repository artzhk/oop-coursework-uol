#include "renderer.h"
#include <sys/ioctl.h>
#include <unistd.h>

Canvas::Canvas() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  width = w.ws_col;
  height = w.ws_row;
  grid = vector<vector<char>>(height, vector<char>(width, ' '));
}

vector<vector<char>> &Canvas::get_grid() { return this->grid; }

int Canvas::get_width() { return this->width; }

int Canvas::get_height() { return this->height; }

void Canvas::rescale() {
  this->grid.resize(height, vector<char>(width, ' '));

  for (vector<char> &row : this->grid) {
    if (row.size() < width) {
      row.resize(width, ' ');
    }
  }
}
