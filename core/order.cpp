#include "./order.h"
#include <cassert>

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


OrderBookType OrderBookMapper::map_string(string *value) {
    if (*value == "ask") return OrderBookType::ask;
    if (*value == "bid") return OrderBookType::bid;
    return OrderBookType::uknown;
}
