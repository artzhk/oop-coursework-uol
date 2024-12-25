#include "../ui/menu/menu.h"
#include "../ui/graph/graph.h"
#include "./candlestick.h"

class Core {
private:
  unique_ptr<Menu> menu;
  unique_ptr<Graph> graph;

public:
  Core(Menu *_menu);
  void run_menu();
};


class Application {
private:
  unique_ptr<Core> core;

public:
  Application(Core *_core);
  void run();
};
