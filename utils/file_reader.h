#include "../core/order.h"
#include <string>
#include <vector>

using namespace std;

class FileReader {
private:
public:
  static vector<string *> read_file(string path);
  static vector<string> *tokenise(string *csvLine, char separator);
  static vector<OrderBookEntry> *read_to_order_book_entry(string path);
};
