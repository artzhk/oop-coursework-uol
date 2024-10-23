#include <iostream>
#include <memory>

using namespace std;

class Menu {
private:
  unique_ptr<int> current_choice;

public:
  Menu() : current_choice(new int(0)) {}

  void set_choice(int value) { *current_choice = value; }

  int get_choice() const { return *current_choice; }

  void request_choice() { cin >> *current_choice; }

  void render() const {
    cout << "==Main Menu==" << endl;
    cout << "1. Print help\n";
    cout << "2. Print exchange stats\n";
    cout << "3. Place an ask\n";
    cout << "4. Place a bid\n";
    cout << "5. Print wallet\n";
    cout << "6. Continue\n";
    cout << "Enter your choice (1-6): ";
  }

  void handle_choice() const {
    cout << "\n\nYou selected: " << *current_choice << endl;
    switch (*current_choice) {
    case 1:
      cout << "Help: This is a simple trading application. Select options "
                   "from the menu to interact.\n";
      break;
    case 2:
      cout << "Exchange stats: No data available right now.\n";
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
};

class Application {
private:
  unique_ptr<Menu> menu;

public:
  Application() : menu(new Menu()) {}

  void run() {
    while (true) {
      menu->render();
      menu->request_choice();
      menu->handle_choice();
    }
  }
};

int main() {
  Application app;
  app.run();
  return -1;
}
