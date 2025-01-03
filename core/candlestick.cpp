#import "candlestick.h"
#import "../utils/logger.h"

vector<Candlestick> CandlestickDataExtractor::getCandlesticks(
    const vector<TemperaturePoint> &points, unsigned int hoursStep) {
  vector<Candlestick> candlesticks{};

  auto *logger = Logger::getInstance(EnvType::DEV);
  for (unsigned int i = 0; i < points.size(); i += hoursStep) {
    float initial = points[i].getTemperature();

    float open = initial;
    float high = initial;
    float low = initial;
    float close = 0;

    string date = points[i].getDate();

    for (unsigned int j = i; j < i + hoursStep; j++) {
      if (j >= points.size()) {
        break;
      }

      if (points[j].getTemperature() > high) {
        high = points[j].getTemperature();
      }

      if (points[j].getTemperature() < low) {
        low = points[j].getTemperature();
      }
    }

    if (i == 0 && close == 0) {
      close = points[i].getTemperature();
    }

    candlesticks.emplace_back(date, open, high, close);
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
  float lowest = candlesticks[0].close;
  for (const Candlestick &candlestick : candlesticks) {
    if (candlestick.close < lowest) {
      lowest = candlestick.close;
    }
  }

  return lowest;
}

float CandlestickProcessor::getHighest(const vector<Candlestick> &candlesticks) {
  float highest = candlesticks[0].close;
  for (const Candlestick &candlestick : candlesticks) {
    if (candlestick.close > highest) {
      highest = candlestick.close;
    }
  }

  return highest;
}
