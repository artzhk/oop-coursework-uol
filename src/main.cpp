#include "../include/graph.h"
#include "../include/menu.h"
#include "../include/logger.h"
#include "../include/fileReader.h"
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main() {
  const std::string name = "./datasets/weather_data.csv";
  if (!FileReader::exists(name)) {
	  std::cout << "File does not exists" << std::endl;
	  return -1;
  }

  GraphParametersDTO graphParameters{10, 10};

  std::vector<FilterDTO<string>> filters{
      FilterDTO<string>("1980-01-01T00:00:00Z|2019-12-31T23:00:00Z",
                        FilterType::timeRange),
      FilterDTO<string>(LocationEnumProcessor::locationToString(EULocation::de),
                        FilterType::location)};

  TemperatureMenuDataTransfer parser{&graphParameters, &filters};

  MenuOptions options{true, false};

  Canvas canvas{};
  Renderer renderer{canvas};

  std::vector<TemperaturePoint> temperatures{
      TemparatureDataExtractor::getTemperatures("./datasets/weather_data.csv")};

  std::vector<Candlestick> candlesticks{
      CandlestickDataExtractor::getCandlesticks(temperatures, 24 * 31)};

  Graph graph{candlesticks, &graphParameters, &filters};

  const std::vector<IRenderable *> renderables{&graph};

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
