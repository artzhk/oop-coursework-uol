#pragma once

#include <vector>

using namespace std;

struct RenderPoint {
  int x;
  int y;
  char symbol;
  RenderPoint(int x, int y, char s) : x{x}, y{y}, symbol{s} {}
};

/// Main instance of a canvas, must be modified and 
/// @method getGrid() vector<vector<char>>&
/// @method resize() void - dynamically change canvas width and height
/// @method getWidth() int
/// @method getHeight() int 
struct Canvas {
  Canvas();
  vector<vector<char>> &getGrid() { return this->grid; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  void resize();

private:
  int width;
  int height;
  vector<vector<char>> grid;
};

struct IRenderable {
  virtual vector<RenderPoint> render(const Canvas &canvas) const = 0;
  virtual ~IRenderable() = default;
};

struct Renderer {
  Renderer(Canvas _canvas);
  void render(const vector<IRenderable *> &renderables);
  const Canvas &getCanvas() const { return canvas; }
  void clearCanvas();

private:
  vector<IRenderable> renderables;
  Canvas canvas;
  vector<vector<char>> modifyGrid(const vector<RenderPoint> &renderPoints);
};
