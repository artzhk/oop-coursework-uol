#include "./core.h"

Core::Core(Menu *_menu, OrderBook *_order_book)
    : menu(_menu), order_book(_order_book) {}

void Core::print_market_stats() {
  while (true) {
    menu->render();
    menu->request_choice();
    menu->handle_choice(order_book.release());
  }
}

Application::Application(Core *_core) : core(_core) {}

void Application::run() { core->print_market_stats(); }
