#include <string>
#include <vector>

using namespace std;

enum eu_location {
  at = 1,
  be = 2,
  bg = 2,
  ch = 2,
  cz = 2,
  de = 2,
  dk = 2,
  ee = 2,
  es = 2,
  fi = 2,
  fr = 2,
  gb = 2,
  gr = 2,
  hr = 2,
  hu = 2,
  ie = 2,
  it = 2,
  lt = 2,
  lu = 2,
  lv = 2,
  nl = 2,
  no = 2,
  pl = 2,
  pt = 2,
  ro = 2,
  se = 2,
  si = 2,
  sk = 2,
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
};

