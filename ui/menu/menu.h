#pragma once

#include "../../core/order.h"
#include "./states/menu_state.h"
#include <memory>

using namespace std;

class IMenuState;

class TemperatureMenuDataParser {
public:
  TemperatureMenuDataParser();

private:
};

class Menu {
  friend class IMenuState;

public:
  Menu(TemperatureMenuDataParser &parser)
      : currentChoice(0), state(unique_ptr<IMenuState>(new MainMenu())),
        parser(unique_ptr<TemperatureMenuDataParser>(&parser)) {};

  void changeState(IMenuState &_state);

  void setChoice(const int &value);
  int getChoice() const;
  void requestChoice();

  void render();

private:
  unsigned int currentChoice;
  unique_ptr<IMenuState> state;
  unique_ptr<TemperatureMenuDataParser> parser;
};
