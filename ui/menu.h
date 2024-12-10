#include "../core/order.h"
#include <memory>

using namespace std;

class Menu {
private:
  unique_ptr<int> current_choice;
  void print_market_stats(OrderBook *order_book) const;

public:
  Menu();

  void set_choice(int value);

  int get_choice() const;
  void request_choice();
  void render() const;
  void handle_choice(OrderBook *order_book) const;
};
