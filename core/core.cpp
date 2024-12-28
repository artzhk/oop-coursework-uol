#include "./core.h"

void Core::run_menu() {
  while (true) {
    menu->run();
  }
}

Application::Application(Core *_core) : core(_core) {}

void Application::run() { core->run_menu(); }

// int main() {
//   Core core{new Menu(), new OrderBook("../datasets/dataset.csv")};

//   core.run_menu();
// }
