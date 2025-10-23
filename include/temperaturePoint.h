#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum EULocation {
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

extern const std::unordered_map<string, EULocation> stringToLocationsMap;

class LocationEnumProcessor {
public:
  static string locationToString(EULocation location);
  static EULocation stringToLocation(const std::string &country);
};

class TemperaturePoint {
public:
  TemperaturePoint(EULocation _location, float _temperature, string _date);

  float getTemperature() const { return temperature; }
  string getDate() const { return date; }
  EULocation getLocation() const { return location; }

private:
  EULocation location;
  float temperature;
  string date;
};

class TemperaturePointsState {
public:
  TemperaturePointsState(const vector<TemperaturePoint> &_points)
      : points(vector<TemperaturePoint>(_points)) {};

  void setData(const vector<TemperaturePoint> &_points);
  const vector<TemperaturePoint> &getData();

private:
  vector<TemperaturePoint> points;
};

class TemparatureDataExtractor {
public:
  static vector<TemperaturePoint> getTemperatures(const string &path);
};
