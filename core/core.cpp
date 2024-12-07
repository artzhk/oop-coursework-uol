#include "./core.h"
#include <iostream>

Core::Core(Menu *_menu, OrderBook *_order_book)
    : menu(_menu), order_book(_order_book) {}

void Core::print_market_stats() {
  for (string const &p : *order_book->get_known_products()) {
    cout << "Product: " << p << endl;
    vector<OrderBookEntry> *entries = order_book->get_orders(
        OrderBookType::ask, p, "2020/03/17 17:01:24.884492");
    cout << "Asks seen: " << entries->size() << endl;
    cout << "Max ask" << OrderBookEntryProcessor::compute_high_price(*entries)
         << endl;
    cout << "Min ask" << OrderBookEntryProcessor::compute_low_price(*entries)
         << endl;
    cout << "Average ask"
         << OrderBookEntryProcessor::compute_low_price(*entries) << endl;
    cout << "Ask Spread" << OrderBookEntryProcessor::compute_low_price(*entries)
         << endl;
  }
}

void Core::run_menu() {
  while (true) {
    menu->render();
    menu->request_choice();
    menu->handle_choice(order_book.release());
  }
}

Application::Application(Core *_core) : core(_core) {}

void Application::run() { core->print_market_stats(); }

// int main() {
//   Core core{new Menu(), new OrderBook("../datasets/dataset.csv")};

//   core.print_market_stats();
// }
