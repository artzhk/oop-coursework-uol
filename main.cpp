#include "core/core.h"
using namespace std;

int main() {
  Core core{new Menu(), new OrderBook("../datasets/dataset.csv")};
  Application app{&core};

  while (1) {
    app.run();
  }
}
