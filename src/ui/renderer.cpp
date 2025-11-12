#include "../../include/renderer.h"
#include "../../include/logger.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

Canvas::Canvas() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  width = w.ws_col;
  height = floor(w.ws_row);
  grid = std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
}

void Canvas::resize() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  this->width = w.ws_col;
  this->height = floor(w.ws_row);
  this->grid =
      std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
}

void Renderer::clearCanvas() {
  LOG_INFO("Clearing canvas");
  std::vector<std::vector<char>> &grid = this->canvas.getGrid();

  for (std::size_t i = 0; i < grid.size(); ++i) {
    for (std::size_t j = 0; j < grid[i].size(); ++j) {
      grid[i][j] = ' ';
    }
  }

  this->canvas.resize();
}

void Renderer::render(const std::vector<IRenderable *> &renderables) {
  LOG_INFO("Rendering\namount of renderables %s",
           std::to_string(renderables.size()).c_str());
  std::vector<RenderPoint> renderPoints{};

  for (unsigned long i = 0; i < renderables.size(); ++i) {
    IRenderable *it = renderables[i];
    if (it == nullptr) {
      continue;
    }

    std::vector<RenderPoint> addPoints = it->render(canvas);
    renderPoints.insert(renderPoints.end(), addPoints.begin(), addPoints.end());
  }

  const std::vector<std::vector<char>> &grid = modifyGrid(renderPoints);

  for (int i = grid.size() - 1; i >= 0; --i) {
    for (std::size_t j = 0; j < grid[i].size(); ++j) {
      std::cout << grid[i][j];
    }
    std::cout << std::endl;
  }

  return;
}

Renderer::Renderer(Canvas _canvas) { canvas = _canvas; }

std::vector<std::vector<char>>
Renderer::modifyGrid(const std::vector<RenderPoint> &renderPoints) {
  LOG_INFO("Modifying Grid");
  std::vector<std::vector<char>> &grid = this->canvas.getGrid();

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
