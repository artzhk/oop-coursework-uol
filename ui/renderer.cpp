#include "renderer.h"
#include "../utils/logger.h"
#include <cmath>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

Canvas::Canvas() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  width = w.ws_col;
  height = floor(w.ws_row * 0.8);
  grid = vector<vector<char>>(height, vector<char>(width, ' '));
}

vector<RenderPoint> IRenderable::render(const Canvas &canvas) const {
  return vector<RenderPoint>{};
}

void Renderer::render(const vector<IRenderable *> &renderables) {

  vector<RenderPoint> renderPoints{};

  for (int i = 0; i < renderables.size(); ++i) {
    auto *it = renderables[i];
    if (it == nullptr) {
      continue;
    }

    vector<RenderPoint> addPoints = it->render(canvas);

    renderPoints.insert(renderPoints.end(), addPoints.begin(), addPoints.end());
  }

  const vector<vector<char>> &grid = modifyGrid(renderPoints);

  for (int i = grid.size() - 1; i > 0; --i) {
    for (int j = 0; j < grid[i].size(); ++j) {
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

  auto *logger = Logger::getInstance(EnvType::DEV);

  // logger->log(to_string(renderPoints.size()));
  // logger->log("Lenght" + to_string(grid[0].size()));
  // logger->log("Height" + to_string(grid.size()));

  for (int i = 0; i < renderPoints.size(); ++i) {
    const int &x = renderPoints[i].x;
    const int &y = renderPoints[i].y;
    const char &symbol = renderPoints[i].symbol;

    // logger->log("X: " + to_string(x) + " Y: " + to_string(y) +
    //         " SYMBOL: " + symbol);
    if ((y >= 0 && y < grid.size()) && (x >= 0 && x < grid[y].size())) {
      grid[y][x] = symbol;
    }
  }

  return grid;
}
