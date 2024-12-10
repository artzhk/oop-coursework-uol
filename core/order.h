#include <memory>
#include <string>
#include <vector>
using namespace std;

enum class OrderBookType { bid, ask, uknown };

class OrderBookEntry {
private:
public:
  OrderBookEntry(string _timestamp, string _product, OrderBookType _type,
                 double _price, double _amount);

  string timestamp;
  string product;
  OrderBookType type;
  double amount;
  double price;
};

class OrderBookMapper {
private:
public:
  static OrderBookType map_string(string *value);
};

class OrderBook {
private:
  unique_ptr<vector<OrderBookEntry>> entries;
  vector<OrderBookEntry> *read_file_to_order_book(const string &path);

public:
  OrderBook(const string &_file_name);
  vector<string> get_known_products();
  vector<OrderBookEntry> get_orders(const OrderBookType &type,const string &product,
                                     const string &timestamp);
};

class OrderBookEntryProcessor {
public:
  static double compute_average_price(vector<OrderBookEntry> &entries);
  static double compute_low_price(vector<OrderBookEntry> &entries);
  static double compute_high_price(vector<OrderBookEntry> &entries);
  static double compute_price_spread(vector<OrderBookEntry> &entries);
};
