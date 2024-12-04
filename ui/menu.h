#include <memory>
#include "../core/order.h"

using namespace std;

class Menu {
private:
  unique_ptr<int> current_choice;

public:
  Menu();

  void set_choice(int value);

  int get_choice() const;
  void request_choice();
  void render() const;
  void handle_choice(OrderBook* order_book) const;
};
