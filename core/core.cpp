#include "./core.h"

Core::Core(Menu *_menu)
    : menu(_menu) {}

void Core::run_menu() {
  while (true) {
    menu->render();
    menu->request_choice();
    menu->handle_choice();
  }
}

Application::Application(Core *_core) : core(_core) {}

void Application::run() { core->run_menu(); }

// int main() {
//   Core core{new Menu(), new OrderBook("../datasets/dataset.csv")};

//   core.run_menu();
// }
