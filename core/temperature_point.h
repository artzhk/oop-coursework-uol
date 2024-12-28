#pragma once

#include <memory>
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

static const unordered_map<string, EULocation> locationsMap = {
    {"at", EULocation::at}, {"be", EULocation::be}, {"bg", EULocation::bg},
    {"ch", EULocation::ch}, {"cz", EULocation::cz}, {"de", EULocation::de},
    {"dk", EULocation::dk}, {"ee", EULocation::ee}, {"es", EULocation::es},
    {"fi", EULocation::fi}, {"fr", EULocation::fr}, {"gb", EULocation::gb},
    {"gr", EULocation::gr}, {"hr", EULocation::hr}, {"hu", EULocation::hu},
    {"ie", EULocation::ie}, {"it", EULocation::it}, {"lt", EULocation::lt},
    {"lu", EULocation::lu}, {"lv", EULocation::lv}, {"nl", EULocation::nl},
    {"no", EULocation::no}, {"pl", EULocation::pl}, {"pt", EULocation::pt},
    {"ro", EULocation::ro}, {"se", EULocation::se}, {"si", EULocation::si},
    {"sk", EULocation::sk}};

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
      : points(unique_ptr<vector<TemperaturePoint>>(
            new vector<TemperaturePoint>(_points))) {};
  void setData(const vector<TemperaturePoint> &_points);
  const vector<TemperaturePoint> &getData();

private:
  unique_ptr<vector<TemperaturePoint>> points;
};

class TemparatureDataExtractor {
public:
  TemparatureDataExtractor();
  static vector<TemperaturePoint> getTemperatures(const string &path);
};
