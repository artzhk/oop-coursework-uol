#include "./order.h"
#include "../utils/file_reader.h"
#include <cassert>
#include <map>
#include <string>

using namespace std;

OrderBookEntry::OrderBookEntry(string _timestamp, string _product,
                               OrderBookType _type, double _amount,
                               double _price)
    : timestamp(_timestamp), product(_product), type(_type), amount(_amount),
      price(_price) {}

double OrderBookEntryProcessor::compute_average_price(
    std::vector<OrderBookEntry> &entries) {
  double sum = 0;
  for (OrderBookEntry &e : entries) {
    sum += e.price;
  }

  sum = sum / entries.size();

  return sum;
}

double
OrderBookEntryProcessor::compute_price_spread(vector<OrderBookEntry> &entries) {
  uint size = entries.size();
  assert(size > 0);

  if (size == 1) {
    return entries[0].price;
  }

  return OrderBookEntryProcessor::compute_high_price(entries) -
         OrderBookEntryProcessor::compute_low_price(entries);
}

double
OrderBookEntryProcessor::compute_high_price(vector<OrderBookEntry> &entries) {
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
OrderBookEntryProcessor::compute_low_price(vector<OrderBookEntry> &entries) {
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
  if (*value == "ask")
    return OrderBookType::ask;
  if (*value == "bid")
    return OrderBookType::bid;
  return OrderBookType::uknown;
}

OrderBook::OrderBook(const string &file_name)
    : entries(read_file_to_order_book(file_name)) {}

vector<string> *OrderBook::get_known_products() {
  vector<string> *products = new vector<string>();
  map<string, bool> *unique_products_map = new map<string, bool>();

  for (OrderBookEntry &e : *entries.release()) {
    (*unique_products_map)[e.product] = true;
  }

  for (const auto &e : *unique_products_map) {
    products->push_back(e.first);
  }

  delete unique_products_map;
  return products;
}

vector<OrderBookEntry> *OrderBook::get_orders(const OrderBookType &type,
                                              const string &product,
                                              const string &timestamp) {
  vector<OrderBookEntry> *result = new vector<OrderBookEntry>();

  for (OrderBookEntry const &e : *entries.release()) {
    if (e.type == type && e.product == product) {
      result->push_back(e);
    }
  }

  return result;
}

vector<OrderBookEntry> *OrderBook::read_file_to_order_book(const string &path) {
  vector<OrderBookEntry> *entries = new vector<OrderBookEntry>();
  vector<string> rows = FileReader::read_file(path);

  for (string row : rows) {
    vector<string> *tokens = FileReader::tokenise(&row, ',');
    OrderBookEntry entry{(*tokens)[0], (*tokens)[1],
                         OrderBookMapper::map_string(&(*tokens)[2]),
                         stod((*tokens)[3]), stod((*tokens)[4])};
    delete tokens;
    entries->push_back(entry);
  }

  return entries;
}

// int main() {
//   OrderBook book("../datasets/dataset.csv");
//   for (const OrderBookEntry &e : *book.get_orders(OrderBookType::bid,
//   "ETH/BTC", "uoae")) {
//     cout << e.product << endl;
//     cout << e.price << endl;
//   }

//   return -1;
// }
