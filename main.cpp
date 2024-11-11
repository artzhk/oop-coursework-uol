#include <cassert>
#include <cstdlib>
#include <iostream>

#include "./ui/menu.h"

using namespace std;

OrderBookEntry::OrderBookEntry(string _timestamp, string _product,
                               OrderBookType _type, double _amount,
                               double _price)
    : timestamp(_timestamp), product(_product), type(_type), amount(_amount),
      price(_price) {}

double OrderBookProcessor::computeAveragePrice(
    std::vector<OrderBookEntry> &entries) const {
  double sum = 0;
  for (OrderBookEntry &e : entries) {
    sum += e.price;
  }

  sum = sum / entries.size();

  return sum;
}

double
OrderBookProcessor::computePriceSpread(vector<OrderBookEntry> &entries) const {
  uint size = entries.size();
  assert(size > 0);

  if (size == 1) {
    return entries[0].price;
  }

  return OrderBookProcessor::computeHighPrice(entries) -
         OrderBookProcessor::computeLowPrice(entries);
}

double
OrderBookProcessor::computeHighPrice(vector<OrderBookEntry> &entries) const {
  uint size = entries.size();
  assert(size > 0);

  double highest = entries[size - 1].price;

  if (size == 1) {
    return highest;
  }

  for (OrderBookEntry &entry : entries) {
    if (entry.price > highest) {
      highest = entry.price;
    }
  }

  return highest;
}

double
OrderBookProcessor::computeLowPrice(vector<OrderBookEntry> &entries) const {
  uint size = entries.size();

  assert(size > 0);

  double lowest = entries[0].price;

  if (size == 1) {
    return lowest;
  }

  for (OrderBookEntry &entry : entries) {
    if (entry.price < lowest) {
      lowest = entry.price;
    }
  }

  return lowest;
}

int main() {
  OrderBookEntry obe1{"2020/03/17 17:01:24.123456", "ETH/BTC",
                      OrderBookType::bid, 0.02193278, 21.99284948};
  OrderBookEntry obe2{"2020/03/17 17:02:35.123456", "ETH/BTC",
                      OrderBookType::ask, 0.23648828, 5.38472786};
  OrderBookEntry obe3{"2020/03/17 17:03:45.123456", "ETH/BTC",
                      OrderBookType::bid, 0.29993292, 8.84165814};

  OrderBookProcessor processor;

  vector<OrderBookEntry> entries;

  entries.push_back(obe1);
  entries.push_back(obe2);
  entries.push_back(obe3);

  cout << "Low Price: " << processor.computeLowPrice(entries) << endl;
  cout << "High Price: " << processor.computeHighPrice(entries) << endl;
  cout << "Average Price: " << processor.computeAveragePrice(entries) << endl;
  cout << "Average Price: " << processor.computePriceSpread(entries) << endl;

  return -1;
}
