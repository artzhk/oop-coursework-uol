#include "candlestick.h"
#include "menu.h"
#include "renderer.h"

class Graph : public IRenderable {
public:
  Graph(const vector<Candlestick> &_candlesticks, GraphParametersDTO *_graphParameters, vector<FilterDTO<string>> *_filters)
      : candlesticks(_candlesticks), graphParameters(_graphParameters), filters(_filters) {}

  vector<RenderPoint> render(const Canvas &canvas) const override;
  void setCandlesticks(const vector<Candlestick> &_candlesticks) { candlesticks = _candlesticks; }

private:
  shared_ptr<GraphParametersDTO> graphParameters;
  shared_ptr<vector<FilterDTO<string>>> filters;
  vector<Candlestick> candlesticks;
  vector<RenderPoint> renderAxes(const Canvas &canvas) const;
  vector<RenderPoint> renderCandlesticks(const Canvas &canvas) const;
};
