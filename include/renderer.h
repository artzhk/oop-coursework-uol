#pragma once

#include <vector>

struct RenderPoint {
  int x;
  int y;
  char symbol;
  RenderPoint(int x, int y, char s) : x{x}, y{y}, symbol{s} {}
};

/// Main instance of a canvas, must be modified and 
/// @method getGrid() std::vector<std::vector<char>>&
/// @method resize() void - dynamically change canvas width and height
/// @method getWidth() int
/// @method getHeight() int 
struct Canvas {
  Canvas();
  std::vector<std::vector<char>> &getGrid() { return this->grid; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  void resize();

private:
  int width;
  int height;
  std::vector<std::vector<char>> grid;
};

/// Main renderable abstraction to inherit by every object 
/// that must be renderable
struct IRenderable {
  virtual std::vector<RenderPoint> render(const Canvas &canvas) const = 0;
  virtual ~IRenderable() = default;
};

// TODO: dude must have a destructor to clear IRenderable 
/// Renders clears and modifiese the grid 
/// @method render(const std::std::vector<const IRenderable&>) void - renders renderable object on 
///  the current canvas
/// @method getCanvas() const Canvas & - returns canvas is operated on
/// @method cleanCanvas() void - clears current canvas
struct Renderer {
  Renderer(Canvas _canvas);
  void render(const std::vector<IRenderable *> &renderables);
  const Canvas &getCanvas() const { return canvas; }
  void clearCanvas();
  ~Renderer();

private:
  std::vector<IRenderable> renderables;
  Canvas canvas;
  std::vector<std::vector<char>> modifyGrid(const std::vector<RenderPoint> &renderPoints);
};
