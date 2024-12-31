#include "./menu.h"
#include "states/menu_state.h"
#include <iostream>
#include <memory>
#include <unistd.h>
#include <unordered_map>

#define ESCAPE '\x1b'
#define ARROW '['
#define UP 'A'
#define DOWN 'B'

using namespace std;

Menu::Menu(const TemperatureMenuDataTransfer &_parser)
    : currentChoice(0), state(new MainMenu()),
      parser(unique_ptr<TemperatureMenuDataTransfer>(
          new TemperatureMenuDataTransfer())),
      coreEvents(unique_ptr<ExternalCoreEvents>(
          new ExternalCoreEvents(false, false))) {};

Menu::~Menu() { delete Menu::instance; }

void Menu::changeState(MenuState *_state) {
  this->state = unique_ptr<MenuState>(_state);
}

void Menu::setChoice(const unsigned int &value) { this->currentChoice = value; }

int Menu::getChoice() { return this->currentChoice; }

void Menu::setParser(TemperatureMenuDataTransfer &_parser) {
  *this->parser = _parser;
}

const TemperatureMenuDataTransfer &Menu::getParser() { return *this->parser; }

void Menu::requestChoice() {
  char input[3];

  read(STDIN_FILENO, input, 3);

  const unsigned int optionsLength = this->state->getOptions().size();

  if (input[0] == ESCAPE) {
    if (input[1] == ARROW) {
      switch (input[2]) {
      case UP:
        this->setChoice((this->currentChoice - 1) % optionsLength);
        break;
      case DOWN:
        this->setChoice((this->currentChoice + 1) % optionsLength);
        break;
      }
    }
  }

  if (input[0] != ESCAPE) {
    switch (input[0]) {
    case 'G':
      this->coreEvents->graph = !this->coreEvents->graph;
      break;
    case 'F':
      this->changeState(new MainMenu());
    case 'j':
      this->setChoice((this->currentChoice + 1) % optionsLength);
      break;
    case 'k':
      this->setChoice((this->currentChoice - 1) % optionsLength);
      break;
    case 'q':
      cout << "Quitting..." << endl;
      exit(0);
      break;
    case ' ':
      this->state->handleChoice(*this, this->currentChoice);
      break;
    }
  }
}

const unordered_map<FilterType, string> filtersMap = { {FilterType::location, "Location"}, {FilterType::timeRange, "Time range"}};

void Menu::run() {
  this->state->render(*this);
  this->requestChoice();
  // this->handleChoice();

  return;
}

void Menu::handleChoice() {
  this->state->handleChoice(*this, this->currentChoice);
}

void Menu::setCoreEvents(bool showGraph) {
  this->coreEvents->graph = showGraph;
}

const ExternalCoreEvents &Menu::getCoreEvents() { return *this->coreEvents; }

Menu *Menu::instance = nullptr;
mutex Menu::mutex_;

Menu *Menu::getInstance(const TemperatureMenuDataTransfer &_parser) {
  lock_guard<mutex> lock(mutex_);

  if (!Menu::instance) {
    Menu::instance = new Menu(_parser);
  }

  return Menu::instance;
}

void TemperatureMenuDataTransfer::setFilters(
    const vector<FilterDTO<string>> &_filters) {
  *this->filters = _filters;
}

const vector<FilterDTO<string>> &TemperatureMenuDataTransfer::getFilters() {
  return *this->filters;
}

void GraphParametersDTO::setScale(const unsigned int &_scale) {
  this->scale = _scale;
}

unsigned int GraphParametersDTO::getScale() { return this->scale; }

void TemperatureMenuDataTransfer::setGraphParameters(
    const GraphParametersDTO &_graphParameters) {
  *this->graphParameters = _graphParameters;
}

const GraphParametersDTO &TemperatureMenuDataTransfer::getGraphParameters() {
  return *this->graphParameters;
}

// int main() {
//   TemperatureMenuDataTransfer *parser = new TemperatureMenuDataTransfer();
//   Menu *menu = Menu::getInstance(*parser);

//   while (1) {
//       menu->run();
//   };
// }
