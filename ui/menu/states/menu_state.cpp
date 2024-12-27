#include "menu_state.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

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
  cout << "Controls: " << endl;
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

MainMenu::MainMenu() {
  title = "Main Menu";
  options = {"1. Help", "2. Weather Graph", "3. Weather Prediction"};
  MenuModeManager::controlMode();
}

void MainMenu::handleChoice(Menu &menu, const unsigned int &choice) {
  if (choice == 1) {
    this->printHelp();
  } else if (choice == 2) {
    menu.changeState(GraphMenu());
  } else {
    cout << "Invalid choice! Please select a number between 1 and "
         << this->options.size() << "." << endl;
  }

  return;
}

GraphMenu::GraphMenu() {
  title = "Graph Menu";
  options = {
      "1. Show Graph",
      "2. Select Countries",
      "2. Filters",
      "3. Back",
  };
  MenuModeManager::controlMode();
}

void GraphMenu::handleChoice(Menu &menu, const unsigned int &choice) {

    return;
}
