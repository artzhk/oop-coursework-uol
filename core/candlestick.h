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

  Candlestick(string _date, float _open, float _high, float _close)
      : date(_date), open(_open), high(_high), close(_close) {}
};

class DataPoint {
private:
  int x;
  int y;

public:
  DataPoint(float _x, float _y) : x(_x), y(_y) {}
};

class CandlestickDataExtractor {
public:
  static vector<Candlestick> getCandlesticks(const vector<TemperaturePoint> &points);
};

class CandlestickProcessor {
public:
  static float getAverageMean(const vector<DataPoint> &candlesticks);
  static float getLowest(const vector<DataPoint> &candlesticks);
  static float geHighest(const vector<DataPoint> &candlesticks);
};

class Plotter {

public:
  static void plot(const vector<DataPoint> &candlesticks);
};
