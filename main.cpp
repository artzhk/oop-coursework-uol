#include "ui/graph/graph.h"
#include "ui/menu/menu.h"
#include "utils/logger.h"
#include <string>

using namespace std;

int main() {
  TemperatureMenuDataTransfer parser{nullptr, nullptr};
  MenuOptions options{true, false};

  Canvas canvas{};
  Renderer renderer{canvas};

  const vector<Candlestick> candlesticks{
      CandlestickDataExtractor::getCandlesticks(
          TemparatureDataExtractor::getTemperatures(
              "./datasets/weather_data.csv"), 24)};

  Graph graph{candlesticks};

  const vector<IRenderable *> renderables{&graph};

  renderer.render(renderables);

  // Menu *menu = Menu::getInstance(parser, options);
  // while (true) {
  //   // menu->run();
  // }
}
