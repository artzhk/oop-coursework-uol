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

class GraphParametersDTO {
public:
  GraphParametersDTO(u_int _xElements, u_int _yElements)
      : xElements(_xElements), yElements(_yElements) {};

  u_int getXElements() { return xElements; }
  void setXElements(u_int _xElements) { xElements = _xElements; }

  u_int getYElements() { return yElements; }
  void setYElements(u_int _yElements) { yElements = _yElements; }

private:
  u_int xElements;
  u_int yElements;
};

enum FilterType { timeRange, location };

extern const std::unordered_map<FilterType, std::string> filtersMap;

template <typename T> class FilterDTO {
public:
  FilterDTO(T _value, FilterType _type) : value(_value), type(_type) {};
  T value;
  FilterType type;
};

class TemperatureMenuDataTransfer {
public:
  TemperatureMenuDataTransfer(GraphParametersDTO *_graphParameters,
                              std::vector<FilterDTO<std::string> > *_filters);

  void setGraphParameters(const GraphParametersDTO &_graphParameters);
  const GraphParametersDTO &getGraphParameters() const;

  void setFilters(const std::vector<FilterDTO<std::string> > &_filters);
  const std::vector<FilterDTO<std::string> > &getFilters() const;

private:
  std::shared_ptr<GraphParametersDTO> graphParameters;
  std::shared_ptr<std::vector<FilterDTO<std::string> > > filters;
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
