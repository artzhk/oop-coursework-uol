#include "candlestick.h"
#include "menu.h"
#include "renderer.h"

/// @brief Main IRenderable instance that must be modified and extended in order
/// to modify graph
/// @see IRenderable
/// @param gParams std::shared_ptr<GraphParameters>
/// @param f std::shared_ptr<vector<Filter<string>>>
/// @param c const vector<Candlestick> & - candlestic const reference
class Graph : public IRenderable {
public:
  Graph(std::shared_ptr<GraphParameters> gParams,
        std::shared_ptr<vector<Filter<string>>> f, const vector<Candlestick> &c)
      : graphParameters(gParams), filters(f), candlesticks(c) {}

  vector<RenderPoint> render(const Canvas &canvas) const override;
  void setCandlesticks(const vector<Candlestick> &_candlesticks) {
    candlesticks = _candlesticks;
  }

private:
  shared_ptr<GraphParameters> graphParameters;
  shared_ptr<vector<Filter<string>>> filters;
  vector<Candlestick> candlesticks;
  vector<RenderPoint> renderAxes(const Canvas &canvas) const;
  vector<RenderPoint> renderCandlesticks(const Canvas &canvas) const;
};
