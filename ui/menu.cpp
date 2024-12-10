#include <iostream>
#include <memory>

#include "../ui/menu.h"

using namespace std;

Menu::Menu() : current_choice(new int(0)) {}

void Menu::set_choice(int value) { *current_choice = value; }

int Menu::get_choice() const { return *current_choice; }

void Menu::request_choice() { cin >> *current_choice; }

void Menu::render() const {
  cout << "==Main Menu==" << endl;
  cout << "1. Print help\n";
  cout << "2. Print exchange stats\n";
  cout << "3. Place an ask\n";
  cout << "4. Place a bid\n";
  cout << "5. Print wallet\n";
  cout << "6. Continue\n";
  cout << "Enter your choice (1-6): ";
}

// Second invoke segmentation fault
// TODO: DEBUG
void Menu::print_market_stats(OrderBook *order_book) const {
  for (string const &p : order_book->get_known_products()) {
    cout << "Product: " << p << endl;
    vector<OrderBookEntry> entries = order_book->get_orders(
        OrderBookType::ask, p, "2020/03/17 17:01:24.884492");
    cout << "Asks seen: " << entries.size() << endl;
    cout << "Max ask" << OrderBookEntryProcessor::compute_high_price(entries)
         << endl;
    cout << "Min ask" << OrderBookEntryProcessor::compute_low_price(entries)
         << endl;
    cout << "Average ask"
         << OrderBookEntryProcessor::compute_average_price(entries) << endl;
    cout << "Ask Spread" << OrderBookEntryProcessor::compute_price_spread(entries)
         << endl;
  }
}

void Menu::handle_choice(OrderBook *order_book) const {
  cout << "\n\nYou selected: " << *current_choice << endl;
  switch (*current_choice) {
  case 1:
    cout << "Help: This is a simple trading application. Select options "
            "from the menu to interact.\n";
    break;
  case 2:
    cout << "Exchange stats: No data available right now.\n";
    print_market_stats(order_book);
    break;
  case 3:
    cout << "Place ask: Enter the amount you'd like to sell.\n";
    break;
  case 4:
    cout << "Place bid: Enter the amount you'd like to buy.\n";
    break;
  case 5:
    cout << "Wallet: Your current balance is $1000.\n";
    break;
  case 6:
    cout << "Continuing...\n";
    break;
  default:
    cout << "Invalid choice! Please select a number between 1 and 6.\n";
    break;
  }
}

int main() { 
    OrderBook order_book("./datasets/dataset.csv");
    Menu menu{}; 
    
    while(1) {
        menu.render();
        menu.request_choice();
        menu.handle_choice(&order_book);
        order_book.get_known_products();
    };
}
