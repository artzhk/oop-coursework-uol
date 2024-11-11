#include <memory>

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
  void handle_choice() const;
};

class Application {
private:
  unique_ptr<Menu> menu;
public:
  Application();
  void run();
};

