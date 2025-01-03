#include <string>
#include <vector>

#include "./temperature_point.h"

using namespace std;

class Candlestick {
public:
  string date;
  float open;
  float high;
  float close;
  float low;

  Candlestick(string _date, float _open, float _high, float _low, float _close)
      : date(_date), open(_open), high(_high), low(_low), close(_close) {}
};

class CandlestickDataExtractor {
public:
  static vector<Candlestick> getCandlesticks(const vector<TemperaturePoint> &points, unsigned int hoursStep = 24, EULocation location = EULocation::de);
};

class CandlestickProcessor {
public:
  static float getAverageMean(const vector<Candlestick> &candlesticks);
  static float getLowest(const vector<Candlestick> &candlesticks);
  static float getHighest(const vector<Candlestick> &candlesticks);
};

