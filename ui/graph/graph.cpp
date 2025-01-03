#include "graph.h"
#include "../../utils/logger.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

#define Y_THRESHOLD 7
#define X_THRESHOLD 8

vector<RenderPoint> Graph::render(const Canvas &canvas) const {
  int width = canvas.getWidth();
  int height = canvas.getHeight();

  vector<RenderPoint> renderPoints{};

  renderPoints = renderAxes(canvas);
  const vector<RenderPoint> &candlesticks = renderCandlesticks(canvas);
  renderPoints.insert(renderPoints.end(), candlesticks.begin(),
                      candlesticks.end());

  return renderPoints;
}

vector<RenderPoint> Graph::renderCandlesticks(const Canvas &canvas) const {
  vector<RenderPoint> renderPoints{};

  int width = canvas.getWidth();
  int height = canvas.getHeight();
  auto *logger = Logger::getInstance(EnvType::DEV);
  u_int size = this->candlesticks.size();

  u_int pagination = 8;

  int ySteps = floor(height / 10);
  int xSteps = floor(width / pagination);

  vector<Candlestick> paginatedCandlesticks = vector<Candlestick>{
      this->candlesticks.begin(), this->candlesticks.begin() + pagination};

  logger->log("Candlesticks high: " + to_string(paginatedCandlesticks[1].high));
  logger->log("Candlesticks low: " + to_string(paginatedCandlesticks[1].low));
  logger->log("Candlesticks open: " + to_string(paginatedCandlesticks[1].open));

  float min = CandlestickProcessor::getLowest(paginatedCandlesticks);
  float max = CandlestickProcessor::getHighest(paginatedCandlesticks);
  float diff = max - min;

  float tempStep = float(diff / 10);

  logger->log("Min: " + to_string(min));
  logger->log("Max: " + to_string(max));

  for (int i = 1; i * xSteps < width && i < paginatedCandlesticks.size(); ++i) {
    const Candlestick &candlestick = paginatedCandlesticks[i];

    for (int j = 0; j < floor(candlestick.date.size() - 7); ++j) {
      renderPoints.emplace_back((i * xSteps) + j, floor(height / 2) - 1,
                                candlestick.date[j]);
    }
  }

  for (int i = 0; i * ySteps < height; ++i) {
    const Candlestick &candlestick = paginatedCandlesticks[i];

    int exp = floor(log10f(tempStep));
    int multiplyFactor = 1;

    if (exp < 0 || exp > 1) {
      multiplyFactor = powf(10, abs(exp));
    }

    string temp =
        string(to_string(((tempStep * i) + min) * multiplyFactor).substr(0, 4));
    if (exp != 0) {
      temp = temp + "e" + to_string(exp);
    }

    for (int j = temp.size(); j > 0; --j) {
      renderPoints.emplace_back(temp.size() - j, i * ySteps,
                                temp[temp.size() - j]);
    }
  }

  for (int i = 1; i < paginatedCandlesticks.size(); ++i) {
    const Candlestick &candlestick = paginatedCandlesticks[i];

    int open = floor(abs((candlestick.open - max) * height) / diff);
    int close = floor(abs((candlestick.close - max) * height) / diff);
    int high = floor(abs((candlestick.high - max) * height) / diff);
    int low = floor(abs((candlestick.low - max) * height) / diff);

    logger->log("Candlestick " + to_string(i));

    // logger->log("Open: " + to_string(candlestick.open));
    // logger->log("Open int: " + to_string(open));
    // logger->log("Close: " + to_string(candlestick.close));
    // logger->log("Close int: " + to_string(close));
    // logger->log("High: " + to_string(candlestick.high));
    // logger->log("High int: " + to_string(high));
    // logger->log("Low: " + to_string(candlestick.low));
    // logger->log("Low int: " + to_string(low));


    renderPoints.emplace_back(i * xSteps, open, 'O');
    renderPoints.emplace_back(i * xSteps, close, 'C');
    renderPoints.emplace_back(i * xSteps, high, 'H');
    renderPoints.emplace_back(i * xSteps, low, 'L');
  }

  return renderPoints;
}

vector<RenderPoint> Graph::renderAxes(const Canvas &canvas) const {
  vector<RenderPoint> renderPoints{};

  int width = canvas.getWidth();
  int height = canvas.getHeight();
  auto *logger = Logger::getInstance(EnvType::DEV);
  u_int size = this->candlesticks.size();

  int ySteps = floor(height / 10);
  int xSteps = floor(width / 8);

  for (int i = Y_THRESHOLD; i < width; ++i) {
    if (i % xSteps == 0) {
      renderPoints.emplace_back(i, floor(height / 2), '+');
      continue;
    } else if (i == width - 1) {
      renderPoints.emplace_back(i, floor(height / 2), '>');
      continue;
    } else {
      renderPoints.emplace_back(i, floor(height / 2), '-');
    }
  }

  for (int i = 0; i < height; ++i) {
    if (i == height - 1) {
      renderPoints.emplace_back(Y_THRESHOLD, i, '^');
      continue;
    } else if (i % ySteps == 0) {
      renderPoints.emplace_back(Y_THRESHOLD, i, '+');
      continue;
    } else {
      renderPoints.emplace_back(Y_THRESHOLD, i, '|');
    }
  }

  return renderPoints;
}
