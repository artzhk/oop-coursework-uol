#include <iostream>
#include <memory>

class Menu {
private:
  std::unique_ptr<int> currentChoice;

public:

  Menu() : currentChoice(new int(0)) {}

  void setChoice(int value) { *currentChoice = value; }

  int getChoice() const { return *currentChoice; }

  void requestChoice() { std::cin >> *currentChoice; }

  void render() const {
    std::cout << "==Main Menu==" << std::endl;
    std::cout << "1. Print help\n";
    std::cout << "2. Print exchange stats\n";
    std::cout << "3. Place an ask\n";
    std::cout << "4. Place a bid\n";
    std::cout << "5. Print wallet\n";
    std::cout << "6. Continue\n";
    std::cout << "Enter your choice (1-6): ";
  }

  void handleChoice() const {
    switch (*currentChoice) {
    case 1:
      std::cout << "Help: This is a simple trading application. Select options "
                   "from the menu to interact.\n";
      break;
    case 2:
      std::cout << "Exchange stats: No data available right now.\n";
      break;
    case 3:
      std::cout << "Place ask: Enter the amount you'd like to sell.\n";
      break;
    case 4:
      std::cout << "Place bid: Enter the amount you'd like to buy.\n";
      break;
    case 5:
      std::cout << "Wallet: Your current balance is $1000.\n";
      break;
    case 6:
      std::cout << "Continuing...\n";
      break;
    default:
      std::cout << "Invalid choice! Please select a number between 1 and 6.\n";
      break;
    }
  }
};

class Application {
private:
  std::unique_ptr<Menu> menu;

public:
  Application() : menu(new Menu()) {}

  void run() {
    while (true) {
      int choice = 0;
      menu->render();
      std::cin >> choice;
      menu->setChoice(choice);
      menu->handleChoice();
    }
  }
};

int main() {
  Application app;
  app.run();
  return -1;
}
