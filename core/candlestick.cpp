#import "candlestick.h"
#import "../utils/fileReader.h"
#import "../utils/logger.h"
#include "temperaturePoint.h"
#include <string>

vector<Candlestick> CandlestickDataExtractor::getCandlesticks(
    const vector<TemperaturePoint> &points,
    const vector<FilterDTO<string>> &filters, unsigned int hoursStep) {
  auto *logger = Logger::getInstance(EnvType::PROD);

  EULocation location = EULocation::uknown;
  DateInterval *dateInterval = nullptr;

  for (const FilterDTO<string> &filter : filters) {
    if (filter.type == FilterType::location) {
        logger->log("Filter value: " + filter.value);
      location = LocationEnumProcessor::stringToLocation(filter.value);
    }

    if (filter.type == FilterType::timeRange) {
      vector<string> tokens = FileReader::tokenise(filter.value, '|');
      dateInterval = new DateInterval(tokens[0], tokens[1]);
    }
  }

  if (dateInterval == nullptr) {
    throw invalid_argument("Invalid date interval");
  }

  vector<TemperaturePoint> filteredPoints = filterPoints(points, location);

  vector<Candlestick> candlesticks =
      createCandlesticks(filteredPoints, dateInterval, hoursStep);

  delete dateInterval;

  return candlesticks;
}

vector<Candlestick> CandlestickDataExtractor::createCandlesticks(
    const vector<TemperaturePoint> &filteredPoints, DateInterval *dateInterval,
    u_int hoursStep) {
  vector<Candlestick> candlesticks{};

  for (unsigned int i = 0; i < filteredPoints.size(); i += hoursStep) {
    const TemperaturePoint &point = filteredPoints[i];
    float initial = point.getTemperature();
    float open;

    if (open == 0) {
      open = initial;
    }

    float high = initial;
    float low = initial;
    float close = 0;

    string date = point.getDate();

    if (dateInterval != nullptr) {
      if (date < dateInterval->start || date > dateInterval->end) {
        continue;
      }
    }

    for (unsigned int j = i; j < i + hoursStep; j++) {
      const TemperaturePoint &everyTimePoint = filteredPoints[j];

      close += everyTimePoint.getTemperature();

      if (j >= filteredPoints.size()) {
        break;
      }

      if (everyTimePoint.getTemperature() > high) {
        high = everyTimePoint.getTemperature();
      }

      if (everyTimePoint.getTemperature() < low) {
        low = everyTimePoint.getTemperature();
      }
    }

    close /= hoursStep;

    if (i == 0 && close == 0) {
      close = point.getTemperature();
    }

    candlesticks.emplace_back(date, open, high, low, close);
    open = close;
  }

  return candlesticks;
}

vector<TemperaturePoint>
CandlestickDataExtractor::filterPoints(const vector<TemperaturePoint> &points,
                                       const EULocation &location) {
  vector<TemperaturePoint> filteredPoints{};

  for (const TemperaturePoint &point : points) {
    if (point.getLocation() != location) {
      continue;
    }

    filteredPoints.emplace_back(point);
  }


  return filteredPoints;
}

vector<Candlestick> CandlestickDataExtractor::getCandlesticks(
    const vector<TemperaturePoint> &points, unsigned int hoursStep,
    EULocation location) {

  auto *logger = Logger::getInstance(EnvType::PROD);

  vector<TemperaturePoint> filteredPoints = filterPoints(points, location);

  vector<Candlestick> paginatedCandlesticks =
      createCandlesticks(filteredPoints, nullptr, hoursStep);

  return paginatedCandlesticks;
}

float CandlestickProcessor::getAverageMean(
    const vector<Candlestick> &candlesticks) {
  float sum = 0;
  for (const Candlestick &candlestick : candlesticks) {
    sum += candlestick.close;
  }

  return sum / candlesticks.size();
}

float CandlestickProcessor::getLowest(const vector<Candlestick> &candlesticks) {
  float lowest = candlesticks[0].low;
  for (const Candlestick &candlestick : candlesticks) {
    if (candlestick.low < lowest) {
      lowest = candlestick.low;
    }
  }

  return lowest;
}

float CandlestickProcessor::getHighest(
    const vector<Candlestick> &candlesticks) {
  float highest = candlesticks[0].high;
  for (const Candlestick &candlestick : candlesticks) {
    if (candlestick.high > highest) {
      highest = candlestick.high;
    }
  }

  return highest;
}
