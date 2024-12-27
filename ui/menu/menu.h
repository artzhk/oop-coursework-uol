#pragma once

#include "../../core/order.h"
#include "./states/menu_state.h"
#include <memory>

using namespace std;

class MenuState;

// TODO: Ootputs this variables as unique single instance in menu and read them in the core
class ExternalCoreEvents {
public:
  bool graph;
  bool filters;
};

class TemperatureMenuDataParser {
public:
  TemperatureMenuDataParser();
  // TODO: parse data from the core here and display if needed
};

class Menu {
  friend class MenuState;
  friend class Core;

public:
  Menu(TemperatureMenuDataParser &parser)
      : currentChoice(0), state(unique_ptr<MenuState>(new MainMenu())),
        parser(unique_ptr<TemperatureMenuDataParser>(&parser)) {};

  void changeState(const MenuState &_state);

  void setChoice(const unsigned int &value);
  int getChoice();
  void requestChoice();
  void handleChoice();

  void run();

private:
  unsigned int currentChoice;
  unique_ptr<MenuState> state;
  unique_ptr<TemperatureMenuDataParser> parser;
};
