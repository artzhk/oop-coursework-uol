#pragma once

#include "menuState.h"

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class ExternalCoreEvents {
public:
  ExternalCoreEvents(bool _graph, bool _filters)
      : graph(_graph), filters(_filters) {}
  bool graph;
  bool filters;
};

// TODO: Options of Graph might be width and height, idk why is it called x,
// y...
// @param x u_int
// @param y u_int
class GraphParameters {
public:
  GraphParameters(u_int x, u_int y) : x(x), y(y) {};

  u_int getX() { return x; }
  void setX(u_int x) { this->x = x; }

  u_int getY() { return y; }
  void setY(u_int y) { this->y = y; }

private:
  u_int x;
  u_int y;
};

// TODO: filters belong to another file
enum FilterType { TimeRange, Location };
inline const char *toString(FilterType t) {
  switch (t) {
  case TimeRange:
    return "Time Range";
  case Location:
    return "Location";
  }
}

extern const std::unordered_map<FilterType, std::string> filtersMap;

template <typename T> class Filter {
public:
  Filter(T _value, FilterType _type) : value(_value), type(_type) {};
  T value;
  FilterType type;
};

/// TODO: Pls understand what it used for
/// @param gParams - graph parameters
/// @param f - vector of filters
class TemperatureMenuDataTransfer {
public:
  TemperatureMenuDataTransfer(
      std::shared_ptr<GraphParameters> gParams,
      std::shared_ptr<std::vector<Filter<std::string>>> f)
      : graphParameters(gParams), filters(f) {}

  void setGraphParameters(const GraphParameters &_graphParameters);
  const GraphParameters &getGraphParameters() const;

  void setFilters(const std::vector<Filter<std::string>> &_filters);
  const std::vector<Filter<std::string>> &getFilters() const;

private:
  std::shared_ptr<GraphParameters> graphParameters;
  std::shared_ptr<std::vector<Filter<std::string>>> filters;
};

class MenuOptions {
public:
  MenuOptions(bool _showControls, bool _showFilters)
      : showControls(_showControls), showFilters(_showFilters) {};

  void setOptions(bool *showControls, bool *showFilters);

  const bool &getShowControls();
  const bool &getShowFilters();

private:
  bool showControls;
  bool showFilters;
};

class Menu {
  friend class MenuState;

public:
  Menu(Menu &other) = delete;
  ~Menu();
  void operator=(const Menu &) = delete;

  static Menu *getInstance(const TemperatureMenuDataTransfer &_parser,
                           const MenuOptions &_options);
  void changeState(MenuState *_state);

  void setChoice(const unsigned int &value);
  int getChoice();
  void handleChoice();
  void handleInput();

  void requestChoice();
  void reqeustInput();

  void setCoreEvents(bool showGraph);
  const ExternalCoreEvents &getCoreEvents();

  void setParser(TemperatureMenuDataTransfer &_parser);
  const TemperatureMenuDataTransfer &getParser();

  void setOptions(const MenuOptions &_parser);
  const MenuOptions &getOptions();

  void run();

private:
  Menu(const TemperatureMenuDataTransfer &_parser, const MenuOptions &_options);

  static Menu *instance;
  // thread-safety
  static std::mutex mutex_;
  unsigned int currentChoice;

  std::unique_ptr<MenuState> state;
  std::unique_ptr<ExternalCoreEvents> coreEvents;
  std::unique_ptr<MenuOptions> options;
  std::shared_ptr<TemperatureMenuDataTransfer> parser;
};
