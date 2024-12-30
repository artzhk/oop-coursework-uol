#include "ui/menu/menu.h"

using namespace std;

int main() {
  TemperatureMenuDataTransfer *parser = new TemperatureMenuDataTransfer();
  Menu *menu = Menu::getInstance(*parser);
  while (true) {
    menu->run();
  }
}
