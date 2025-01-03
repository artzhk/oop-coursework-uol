#include <vector>

using namespace std;

class RenderPoint {
public:
  int x;
  int y;
  char symbol;
  RenderPoint(int _x, int _y, char _symbol) : x(_x), y(_y), symbol(_symbol) {}
};

class Canvas {
public:
  Canvas();
  vector<vector<char>> &getGrid() { return this->grid; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }

private:
  int width;
  int height;
  vector<vector<char>> grid;
};

class IRenderable {
public:
  virtual vector<RenderPoint> render(const Canvas &canvas) const = 0;
  virtual ~IRenderable() = default;
};

class Renderer {
public:
  Renderer(Canvas _canvas);
  void render(const vector<IRenderable*> &renderables);
  const Canvas &getCanvas() const { return canvas; }

private:
  vector<IRenderable> renderables;
  Canvas canvas;
  vector<vector<char>> modifyGrid(const vector<RenderPoint> &renderPoints);
};
