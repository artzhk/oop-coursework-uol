#include "menu_state.h"
#include "../../../core/temperature_point.h"
#include "../../../utils/terminalTextStyles.h"
#include "../menu.h"

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <utility>

MenuMode MenuModeManager::mode = MenuMode::input;
struct termios MenuModeManager::oldt, MenuModeManager::newt;

void MenuModeManager::controlMode() {

  if (mode == MenuMode::control) {
    return;
  }

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  mode = MenuMode::control;

  return;
}

void MenuModeManager::inputMode() {
  if (mode == MenuMode::input) {
    return;
  }

  tcsetattr(STDIN_FILENO, TCSADRAIN, &oldt);

  mode = MenuMode::input;

  return;
}

void MenuState::printControlsHelp() {
  using namespace terminalTextStyles;

  cout << "Controls: " << endl;
  cout << "  - Type " << BOLD << "\"Shift + i\"" << RESET
       << "to hide this help. " << endl;
  cout << "  - Type \"Shift + g\" to display graph. " << endl;
  cout << "  - Type \"Shift + f\" to display filters. " << endl;
  cout << "  - Use the arrow keys to navigate the menu." << endl;
  cout << "  - Or use j, k, h, l to navigate the menu." << endl;
  cout << "  - Press 'Enter' to select an option." << endl;
  cout << "  - Press 'q' to quit the application." << endl;
  return;
}

void MenuState::render(Menu &menu) {
  cout << "==== " << this->title << " ====" << endl;

  if (MenuModeManager::mode == MenuMode::control) {
    this->printControlsHelp();
  }

  for (unsigned int i = 0; i < options.size(); i++) {
    if (i == menu.getChoice()) {
      cout << " > " << options[i] << " < " << endl;
    } else {
      cout << "   " << options[i] << "   " << endl;
    }
  }

  return;
}

void MenuState::handleChoice(Menu &menu, const unsigned int &optionIndex) {
  cout << "Invalid choice! Please select a number between 1 and "
       << this->options.size() << "." << endl;
  return;
}

// void MenuState::displayInputField(Menu &menu) {
//   cout << "Input the value" << endl;
//   MenuModeManager::inputMode();

//   return;
// }

MainMenu::MainMenu() {
  title = "Main Menu";
  options = {"1. Help", "2. Weather Graph", "3. Weather Prediction",
             "4. Select country", "5. Quit"};
  MenuModeManager::controlMode();
}

void MainMenu::render(Menu &menu) { MenuState::render(menu); }

void MainMenu::handleChoice(Menu &menu, const unsigned int &optionIndex) {
  if (optionIndex + 1 == 1) {
    this->printHelp();
  } else if (optionIndex + 1 == 2) {
    menu.changeState(new GraphMenu());
  } else if (optionIndex + 1 == 3) {
    menu.changeState(new GraphMenu());
  } else if (optionIndex + 1 == 4) {
    menu.changeState(new CountrySelectionMenu());
  } else if (optionIndex + 1 == 5) {
    exit(0);
  } else {
    cout << "Invalid choice! Please select a number between 1 and "
         << this->options.size() << "." << endl;
  }

  return;
}

void MainMenu::printHelp() {
  cout << "This is a weather application that displays weather data for "
       << "different countries. " << endl;
}

void MainMenu::printControlsHelp() { MenuState::printControlsHelp(); }

GraphMenu::GraphMenu() {
  title = "Graph Menu";
  options = {
      "1. Graph Settings",
      "2. Filters",
      "3. Back",
  };
  MenuModeManager::controlMode();
}

void GraphMenu::render(Menu &menu) {
  MenuState::render(menu);
  return;
}

void GraphMenu::handleChoice(Menu &menu, const unsigned int &optionIndex) {
  if (optionIndex + 1 == 1) {
    menu.changeState(new MainMenu());
  } else if (optionIndex + 1 == 2) {
    menu.changeState(new FilterMenu());
  } else if (optionIndex + 1 == 3) {
    menu.changeState(new MainMenu());
  } else {
    cout << "Invalid choice! Please select a number between 1 and "
         << this->options.size() << "." << endl;
  }

  return;
}

void GraphMenu::printControlsHelp() {
  MenuState::printControlsHelp();
  return;
}

CountrySelectionMenu::CountrySelectionMenu() {
  title = "Select Country";
  // convert enum values to the vector of string
  options = countries();
  MenuModeManager::controlMode();
}

void CountrySelectionMenu::render(Menu &menu) {
  if (options.size()) {
    cout << "Invalid countries size" << endl;
  }

  if (options.size() == 1) {
    cout << "1. " << options[0] << endl;
  }

  for (unsigned int i = 1; i < options.size(); i++) {
    if (menu.getChoice() == i) {
      if (i % 2 == 1) {
        cout << i << ". " << options[i - 1] << " | " << " > " << (i + 1) << ". "
             << options[i] << " < " << endl;

        continue;
      }

      cout << " > " << i << ". " << options[i - 1] << " < " << " | " << (i + 1)
           << ". " << options[i] << endl;
    } else {
      cout << i << ". " << options[i - 1] << " | " << (i + 1) << ". "
           << options[i] << endl;
    }
  }

  return;
}


void FilterMenu::printControlsHelp() {
    MenuState::printControlsHelp();
}

void CountrySelectionMenu::handleChoice(Menu &menu,
                                        const unsigned int &optionIndex) {
  if (optionIndex >= options.size()) {
    cout << "Invalid choice! Please select a number between 1 and "
         << this->options.size() << "." << endl;
    return;
  }
}

void CountrySelectionMenu::printControlsHelp() {
  MenuState::printControlsHelp();
}

vector<string> CountrySelectionMenu::countries() {
  vector<string> countries{};

  for (const pair<string, EULocation> &locationPair : locationsMap) {
    if (locationPair.second == EULocation::uknown) {
      continue;
    }

    countries.emplace_back(locationPair.first);
  }

  return countries;
}

FilterMenu::FilterMenu() {
  options = generateFilters();
  title = "Filter Menu";
  MenuModeManager::controlMode();
}

void FilterMenu::render(Menu &menu) {
  cout << "==== " << this->title << " ====" << endl;
  cout << "==== " << "Select Filter to Edit it." << " ====" << endl;

  if (MenuModeManager::mode == MenuMode::control) {
    this->printControlsHelp();
  }

  for (unsigned int i = 0; i < options.size(); i++) {
    if (i == menu.getChoice()) {
      cout << " > " << options[i] << " < " << endl;
    } else {
      cout << "   " << options[i] << "   " << endl;
    }
  }

  return;
}

void FilterMenu::setFiltersView(const vector<FilterDTO<string>> &filtersView) {
  this->filtersView = filtersView;
}

vector<FilterDTO<string>> FilterMenu::getFiltersView() { return filtersView; }

vector<string> FilterMenu::generateFilters() {
  vector<string> options{};
  vector<FilterDTO<string>> filtersView{};

  unsigned int i = 1;
  for (const pair<FilterType, string> &filterPair : filtersMap) {
    options.emplace_back(to_string(i) + ". " + filterPair.second);
    filtersView.emplace_back(FilterDTO<string>("", filterPair.first));
    ++i;
  }

  setFiltersView(filtersView);
  options.emplace_back(to_string(i) + ". Back");

  return options;
}

void FilterMenu::handleChoice(Menu &menu, const unsigned int &optionIndex) {
  if (optionIndex >= options.size() || optionIndex < 0) {
    cout << "Invalid choice! Please select a number between 1 and "
         << this->options.size() << "." << endl;
    return;
  }
  vector<FilterDTO<string>> filtersView = getFiltersView();

  if (options.size() == optionIndex + 1) {
      menu.changeState(new FilterMenu());
      return;
  }

  MenuModeManager::inputMode();

  cout << "Enter the value for the filter: "
       << filtersMap.at(filtersView[optionIndex].type) << endl;

  string value;
  cin >> value;

  filtersView[optionIndex].value = value;

  TemperatureMenuDataTransfer parser = menu.getParser();
  vector<FilterDTO<string>> filters = parser.getFilters();

  for (unsigned int i = 0; i < filters.size(); i++) {
    if (filters[i].type == filtersView[optionIndex].type) {
      filters[i].value = filtersView[optionIndex].value;
      break;
    }
  }

  parser.setFilters(filters);
  menu.setParser(parser);

  MenuModeManager::controlMode();

  return;
}
