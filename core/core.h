#include "../ui/menu.h"

class Core {
private:
  unique_ptr<Menu> menu;
  unique_ptr<OrderBook> order_book;

public:
  Core(Menu *_menu, OrderBook *_order_book);
  void init();
  void print_market_stats();
  void run_menu();
  void enter_bid();
  void enter_offer();
};

class Application {
private:
  unique_ptr<Core> core;

public:
  Application(Core *_core);
  void run();
};
