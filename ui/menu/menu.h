#pragma once

#include "../../core/order.h"
#include "../../core/temperature_point.h"
#include "states/menu_state.h"

#include <memory>
#include <mutex>

using namespace std;

// class GraphMenu;
// class CountrySelectionMenu;
// class FilterMenu;
// class WeatherPredictionMenu;

// TODO: Ootputs this variables as unique single instance in menu and read them
// in the core
class ExternalCoreEvents {
public:
  ExternalCoreEvents(bool _graph, bool _filters)
      : graph(_graph), filters(_filters) {}
  bool graph;
  bool filters;
};

class GraphParametersDTO {
public:
  GraphParametersDTO() : scale(0) {};
  void setScale(const unsigned int &_scale);
  unsigned int getScale();
private: 
  unsigned int scale;
};

class FiltersDTO {
public:
  FiltersDTO() : timeRange(make_pair("1980-01-01T00:00:00Z", "2019-12-31T23:00:00Z")), location(EULocation::uknown) {};
  void setTimeRange(const pair<string, string> &_timeRange);
  void setLocation(const EULocation &_location);
  const pair<string, string> &getTimeRange();
  const EULocation &getLocation();
private: 
  pair<string, string> timeRange;
  EULocation location;
};

class TemperatureMenuDataTransfer {
public:
  TemperatureMenuDataTransfer() : graphParameters(new GraphParametersDTO()), filters(new FiltersDTO()) {};

  void setGraphParameters(const GraphParametersDTO &_graphParameters);
  void setFilters(const FiltersDTO &_filters);
  const FiltersDTO &getFilters();
  const GraphParametersDTO &getGraphParameters();
private:
  unique_ptr<GraphParametersDTO> graphParameters;
  unique_ptr<FiltersDTO> filters;
};

class Menu {
  friend class MenuState;

public:
  Menu(Menu &other) = delete;
  void operator=(const Menu &) = delete;

  static Menu *getInstance(const TemperatureMenuDataTransfer &_parser);
  void changeState(const MenuState &_state);

  void setChoice(const unsigned int &value);
  int getChoice();
  void requestChoice();
  void handleChoice();

  void setCoreEvents(bool showGraph);
  const ExternalCoreEvents &getCoreEvents();

  void run();

private:
  Menu(const TemperatureMenuDataTransfer &_parser);

  static Menu *instance;
  // thread-safety
  static mutex mutex_;
  unsigned int currentChoice;

  unique_ptr<MenuState> state;
  unique_ptr<ExternalCoreEvents> coreEvents;
  unique_ptr<TemperatureMenuDataTransfer> parser;
};
