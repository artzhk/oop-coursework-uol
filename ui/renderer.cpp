#include "renderer.h"
#include <cmath>
#include <sys/ioctl.h>
#include <unistd.h>

Canvas::Canvas() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  width = w.ws_col;
  height = floor(w.ws_row * 0.8);
  grid = vector<vector<char>>(height, vector<char>(width, ' '));
}

void Canvas::rescale() {
  this->grid.resize(height, vector<char>(width, ' '));

  for (vector<char> &row : this->grid) {
    if (row.size() < width) {
      row.resize(width, ' ');
    }
  }
}
