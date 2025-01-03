#import "candlestick.h"
#import "../utils/logger.h"
#include "temperature_point.h"

vector<Candlestick> CandlestickDataExtractor::getCandlesticks(
    const vector<TemperaturePoint> &points, unsigned int hoursStep,
    EULocation location) {
  vector<Candlestick> candlesticks{};

  auto *logger = Logger::getInstance(EnvType::DEV);

  vector<TemperaturePoint> filteredPoints{};

  for (const TemperaturePoint &point : points) {
    if (point.getLocation() != location) {
      continue;
    }

    filteredPoints.emplace_back(point);
  }

  for (unsigned int i = 0; i < filteredPoints.size(); i += hoursStep) {
    const TemperaturePoint &point = filteredPoints[i];
    float initial = point.getTemperature();

    float open = initial;
    float high = initial;
    float low = initial;
    float close = 0;

    string date = point.getDate();

    for (unsigned int j = i; j < i + hoursStep; j++) {
      const TemperaturePoint &everyTimePoint = filteredPoints[j];
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

    if (i == 0 && close == 0) {
      close = point.getTemperature();
    }

    candlesticks.emplace_back(date, open, high, low, close);
    close = open;
  }

  logger->log("Candlesticks size: " + to_string(candlesticks.size()));

  return candlesticks;
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
