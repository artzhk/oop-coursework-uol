#include "ui/graph/graph.h"
#include "ui/menu/menu.h"
#include "utils/logger.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main() {
  GraphParametersDTO graphParameters{10, 10};
  vector<FilterDTO<string>> filters{
      FilterDTO<string>("1980-01-01T00:00:00Z|2019-12-31T23:00:00Z",
                        FilterType::timeRange),
      FilterDTO<string>(LocationEnumProcessor::locationToString(EULocation::de),
                        FilterType::location)};

  TemperatureMenuDataTransfer parser{&graphParameters, &filters};

  MenuOptions options{true, false};

  Canvas canvas{};
  Renderer renderer{canvas};

  vector<TemperaturePoint> temperatures{
      TemparatureDataExtractor::getTemperatures("./datasets/weather_data.csv")};

  vector<Candlestick> candlesticks{
      CandlestickDataExtractor::getCandlesticks(temperatures, 24 * 31)};

  Graph graph{candlesticks, &graphParameters, &filters};

  const vector<IRenderable *> renderables{&graph};

  Menu *menu = Menu::getInstance(parser, options);

  while (true) {
    graph.setCandlesticks(CandlestickDataExtractor::getCandlesticks(
        temperatures, filters, 24 * 31));
    renderer.render(renderables);
    menu->run();
    renderer.clearCanvas();
    cout << "\x1B[2J\x1B[H";
  }
}
