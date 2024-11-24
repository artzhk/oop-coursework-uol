#include <cassert>
#include <cstdlib>
#include <iostream>

#include "./utils/file_reader.h"

using namespace std;

int main() {
  // OrderBookEntry obe1{"2020/03/17 17:01:24.123456", "ETH/BTC",
  //                     OrderBookType::bid, 0.02193278, 21.99284948};
  // OrderBookEntry obe2{"2020/03/17 17:02:35.123456", "ETH/BTC",
  //                     OrderBookType::ask, 0.23648828, 5.38472786};
  // OrderBookEntry obe3{"2020/03/17 17:03:45.123456", "ETH/BTC",
  //                     OrderBookType::bid, 0.29993292, 8.84165814};

  // OrderBookProcessor processor;

  // vector<OrderBookEntry> entries;

  // entries.push_back(obe1);
  // entries.push_back(obe2);
  // entries.push_back(obe3);

  // cout << "Low Price: " << processor.computeLowPrice(entries) << endl;
  // cout << "High Price: " << processor.computeHighPrice(entries) << endl;
  // cout << "Average Price: " << processor.computePriceSpread(entries) << endl;
  // cout << "Average Price: " << processor.computeAveragePrice(entries) <<
  // endl;
  //

  vector<OrderBookEntry> *entries =
      FileReader().read_to_order_book_entry("./dataset.csv");

  for (OrderBookEntry entry : *entries) {
    cout << entry.timestamp << endl;
    cout << entry.amount << endl;
    cout << entry.product << endl;
    cout << entry.price << endl;
  }

  return -1;
}
