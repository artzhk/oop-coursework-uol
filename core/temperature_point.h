#include <string>
#include <vector>
#include "./candlestick.h"

using namespace std;

enum eu_location {
  at = 0,
  be = 1,
  bg = 2,
  ch = 3,
  cz = 4,
  de = 5,
  dk = 6,
  ee = 7,
  es = 8,
  fi = 9,
  fr = 10,
  gb = 11,
  gr = 12,
  hr = 13,
  hu = 14,
  ie = 15,
  it = 16,
  lt = 17,
  lu = 18,
  lv = 19,
  nl = 20,
  no = 21,
  pl = 22,
  pt = 23,
  ro = 24,
  se = 25,
  si = 26,
  sk = 27,
  uknown = 255,
};

class TemperaturePoint {
public:
  TemperaturePoint(eu_location _location, float _temperature, string date);
  eu_location location;
  float temperature;
  string date;
};

class TemparatureDataExtractor {
    public: 
        TemparatureDataExtractor();
        static vector<TemperaturePoint> get_temperature_data(const string &path);
        static vector<DataPoint> get_points(const vector<TemperaturePoint> &points);
};

