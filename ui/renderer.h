#include <vector>

using namespace std;

class IRenderable {
public:
  virtual void render(vector<vector<char>> &grid) = 0;
};

class Canvas {
private:
  int width;
  int height;
  vector<vector<char>> grid;

public:
  Canvas();
  void rescale();
  vector<vector<char>> &get_grid();
  int get_width();
  int get_height();
};

class Renderer {
private:
  vector<IRenderable> renderables;
  Canvas canvas;
  void render();

public:
  void add_renderable(IRenderable renderable);
};
