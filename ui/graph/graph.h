#include "../../core/candlestick.h"
#include "../renderer.h"

class Graph : public IRenderable {
public:
  Graph(const vector<Candlestick> &_candlesticks)
      : candlesticks(_candlesticks) {}

  vector<RenderPoint> render(const Canvas &canvas) const override;

private:
  const vector<Candlestick> &candlesticks;
  vector<RenderPoint> renderAxes(const Canvas &canvas) const;
  vector<RenderPoint> renderCandlesticks(const Canvas &canvas) const;
};
