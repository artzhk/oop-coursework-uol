#include "core/core.h"
using namespace std;

int main() {
  Menu *menu = new Menu();
  OrderBook *order_book = new OrderBook("./datasets/dataset.csv");
  Core core{menu, order_book};
  Application app{&core};

  while (1) {
    app.run();
  }
}
