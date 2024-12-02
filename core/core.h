#include "../ui/menu.h"

class Core {
public:
  Core(Menu* menu);
  void init();
private: 
  void print_market_stats();
  void enter_offer();
  void enter_bid();
};
