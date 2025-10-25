#pragma once

#include <string>
#include <vector>

#include "menu.h"
#include "temperaturePoint.h"

using namespace std;

class Candlestick {
public:
  string date;
  float open;
  float high;
  float close;
  float low;

  Candlestick(string _date, float _open, float _high, float _low, float _close)
      : date(_date), open(_open), high(_high), close(_close), low(_low) {}
};

class DateInterval {
public:
  string start;
  string end;
  DateInterval(string _start, string _end) : start(_start), end(_end) {}
};

class CandlestickDataExtractor {
public:
  static vector<Candlestick>
  getCandlesticks(const vector<TemperaturePoint> &points,
                  const vector<Filter<string>> &filters,
                  unsigned int hoursStep = 24);

  static vector<Candlestick>
  getCandlesticks(const vector<TemperaturePoint> &points,
                  unsigned int hoursStep = 24,
                  EULocation location = EULocation::de);

private:
  static vector<TemperaturePoint>
  filterPoints(const vector<TemperaturePoint> &points,
               const EULocation &location);
  static vector<Candlestick>
  createCandlesticks(const vector<TemperaturePoint> &filteredPoints,
                     DateInterval *dateInterval, u_int hoursStep);
};

class CandlestickProcessor {
public:
  static float getAverageMean(const vector<Candlestick> &candlesticks);
  static float getLowest(const vector<Candlestick> &candlesticks);
  static float getHighest(const vector<Candlestick> &candlesticks);
};
