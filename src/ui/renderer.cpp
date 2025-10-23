#include "../../include/renderer.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

Canvas::Canvas() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  width = w.ws_col;
  height = floor(w.ws_row);
  grid = vector<vector<char>>(height, vector<char>(width, ' '));
}

void Canvas::resize() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  this->width = w.ws_col;
  this->height = floor(w.ws_row);
  this->grid = vector<vector<char>>(height, vector<char>(width, ' '));
}

// vector<RenderPoint> IRenderable::render(const Canvas &canvas) const {
//   return vector<RenderPoint>{};
// }

void Renderer::clearCanvas() {
  vector<vector<char>> &grid = this->canvas.getGrid();

  for (std::size_t i = 0; i < grid.size(); ++i) {
    for (std::size_t j = 0; j < grid[i].size(); ++j) {
      grid[i][j] = ' ';
    }
  }

  this->canvas.resize();
}

void Renderer::render(const vector<IRenderable *> &renderables) {

  vector<RenderPoint> renderPoints{};

  for (unsigned long i = 0; i < renderables.size(); ++i) {
    auto *it = renderables[i];
    if (it == nullptr) {
      continue;
    }

    vector<RenderPoint> addPoints = it->render(canvas);

    renderPoints.insert(renderPoints.end(), addPoints.begin(), addPoints.end());
  }

  const vector<vector<char>> &grid = modifyGrid(renderPoints);

  for (int i = grid.size() - 1; i >= 0; --i) {
    for (std::size_t j = 0; j < grid[i].size(); ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }

  return;
}

Renderer::Renderer(Canvas _canvas) { canvas = _canvas; }

vector<vector<char>>
Renderer::modifyGrid(const vector<RenderPoint> &renderPoints) {
  vector<vector<char>> &grid = this->canvas.getGrid();

  // auto *logger = Logger::getInstance(EnvType::PROD);

  for (unsigned int i = 0; i < renderPoints.size(); ++i) {
    const int &x = renderPoints[i].x;
    const int &y = renderPoints[i].y;
    const char &symbol = renderPoints[i].symbol;

    if ((y >= 0 && (std::size_t)y < grid.size()) &&
        (x >= 0 && (std::size_t)x < grid[y].size())) {
      grid[y][x] = symbol;
    }
  }

  return grid;
}
