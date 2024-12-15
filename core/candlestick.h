#include <string>

using namespace std;

class Candlestick {
public:
  string date;
  float open;
  float high;
  float close;
  Candlestick(string _date, float _open, float _high, float _close);
};
