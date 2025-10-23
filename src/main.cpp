#include "../include/fileReader.h"
#include "../include/graph.h"
#include "../include/menu.h"
#include "../include/timing.h"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  timing::elapsed_ms();
  const std::string name = "./datasets/weather_data.csv";
  if (!FileReader::exists(name)) {
    std::cout << "File does not exists" << std::endl;
    std::cout << timing::elapsed_ms() << std::endl;
    return -1;
  }

  shared_ptr<GraphParameters> graphParameters(new GraphParameters{10, 10});

  shared_ptr<std::vector<Filter<string>>> filters(
      new std::vector<Filter<string>>{
          Filter<string>("1980-01-01T00:00:00Z|2019-12-31T23:00:00Z",
                         FilterType::timeRange),
          Filter<string>(
              LocationEnumProcessor::locationToString(EULocation::de),
              FilterType::location)});

  TemperatureMenuDataTransfer parser{graphParameters, filters};

  MenuOptions options{true, false};

  Canvas canvas{};
  Renderer renderer{canvas};

  std::vector<TemperaturePoint> temperatures{
      TemparatureDataExtractor::getTemperatures("./datasets/weather_data.csv")};

  std::vector<Candlestick> candlesticks{
      CandlestickDataExtractor::getCandlesticks(temperatures, 24 * 31)};

  Graph graph{graphParameters, filters, candlesticks};

  const std::vector<IRenderable *> renderables{&graph};

  Menu *menu = Menu::getInstance(parser, options);

  while (true) {
    graph.setCandlesticks(CandlestickDataExtractor::getCandlesticks(
        temperatures, *filters.get(), 24 * 31));
    renderer.render(renderables);
    menu->run();
    renderer.clearCanvas();
    cout << "\x1B[2J\x1B[H";
  }
}
