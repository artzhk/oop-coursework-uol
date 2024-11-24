#include <cassert>
#include <cstdlib>
#include <iostream>

#include "./utils/file_reader.h"

using namespace std;

int main() {
  vector<OrderBookEntry> *entries =
      FileReader().read_to_order_book_entry("./dataset.csv");

  for (OrderBookEntry entry : *entries) {
    cout << "------" << endl;
    cout << entry.timestamp << endl;
    cout << entry.amount << endl;
    cout << entry.product << endl;
    cout << entry.price << "\n" << endl;
  }

  return -1;
}
