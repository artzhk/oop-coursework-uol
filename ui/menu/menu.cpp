#include "./menu.h"
#include "states/menu_state.h"
#include <iostream>
#include <memory>
#include <unistd.h>

#define ESCAPE '\x1b'
#define ARROW '['
#define UP 'A'
#define DOWN 'B'

using namespace std;

void Menu::changeState(const MenuState &_state) { *this->state = _state; }

void Menu::setChoice(const unsigned int &value) { this->currentChoice = value; }

int Menu::getChoice() { return this->currentChoice; }

void Menu::requestChoice() {
  char input[3];
  read(STDIN_FILENO, input, 3);

  const unsigned int optionsLength = this->state->getOptions().size();

  if (input[0] == ESCAPE) {
    if (input[1] == ARROW) {
      switch (input[2]) {
      case UP:
        this->setChoice((this->currentChoice - 1) % optionsLength);
        break;
      case DOWN:
        this->setChoice((this->currentChoice + 1) % optionsLength);
        break;
      }
    }
  }

  if (input[0] != ESCAPE) {
    switch (input[0]) {
    case 'j':
      this->setChoice((this->currentChoice - 1) % optionsLength);
      break;
    case 'k':
      this->setChoice((this->currentChoice + 1) % optionsLength);
      break;
    case 'q':
      cout << "Quitting..." << endl;
      exit(0);
      break;
    case '\n':
      this->state->handleChoice(*this, this->currentChoice);
      break;
    }
  }
}

void Menu::run() { 
    this->state->render(*this); 
    this->requestChoice();
    this->handleChoice();
}

void Menu::handleChoice() {
  this->state->handleChoice(*this, this->currentChoice);
}

// int main() {
//   OrderBook order_book("./datasets/dataset.csv");
//   Menu menu{};

//   while (1) {
//     menu.render();
//     menu.request_choice();
//     menu.handle_choice(&order_book);
//     order_book.get_known_products();
//   };
// }
