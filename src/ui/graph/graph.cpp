#include "../../../include/graph.h"
#include "../../../include/logger.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

#define Y_THRESHOLD 7
#define X_THRESHOLD 8

vector<RenderPoint> Graph::render(const Canvas &canvas) const {
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

  u_int xElementsAmount = this->graphParameters->getX();
  u_int yElementsAmount = this->graphParameters->getY();

  auto *logger = Logger::getInstance(EnvType::PROD);

  int ySteps = floor(height / yElementsAmount);
  int xSteps = floor(width / xElementsAmount);

  vector<Candlestick> paginatedCandlesticks = vector<Candlestick>{
      this->candlesticks.begin(), this->candlesticks.begin() + xElementsAmount};

  float min = CandlestickProcessor::getLowest(paginatedCandlesticks);
  float max = CandlestickProcessor::getHighest(paginatedCandlesticks);
  float diff = max - min;

  logger->log("Min: " + to_string(min));
  logger->log("Max: " + to_string(max));

  float tempStep = float(diff / yElementsAmount);

  for (int i = 1;
       i * xSteps < width && (std::size_t)i < paginatedCandlesticks.size();
       ++i) {
    const Candlestick &candlestick = paginatedCandlesticks[i - 1];

    for (int j = 0; j < floor(candlestick.date.size() - 7); ++j) {
      renderPoints.emplace_back((i * xSteps) + j + 1, floor(height / 2) - 1,
                                candlestick.date[j]);
    }
  }

  for (int i = 0; i * ySteps < height; ++i) {
    int exp = floor(log10f(tempStep));
    int multiplyFactor = 1;

    if (exp < 0 || exp >= 2) {
      multiplyFactor = powf(10, abs(exp));
    }

    string temp =
        string(to_string(((tempStep * i) + min) * multiplyFactor).substr(0, 5));
    if (exp != 0) {
      temp = temp + "e" + to_string(exp);
    }

    for (int j = temp.size(); j > 0; --j) {
      renderPoints.emplace_back(temp.size() - j, i * ySteps,
                                temp[temp.size() - j]);
    }
  }

  for (std::size_t i = 1; i < paginatedCandlesticks.size(); ++i) {
    const Candlestick &candlestick = paginatedCandlesticks[i - 1];

    int open = floor(abs((candlestick.open - min) * height) / diff);
    int close = floor(abs((candlestick.close - min) * height) / diff);
    int high = floor(abs((candlestick.high - min) * height) / diff);
    int low = floor(abs((candlestick.low - min) * height) / diff);

    for (int j = 0; j < abs(high - low); ++j) {
      if (high > low) {
        renderPoints.emplace_back(i * xSteps, low + j, '|');
      } else {
        renderPoints.emplace_back(i * xSteps, high + j, '|');
      }
    }

    for (int j = 0; j < abs(open - close); ++j) {
      if (open > close) {
        if (0 == j) {
          renderPoints.emplace_back(i * xSteps, close + j, 'v');
          continue;
        }
        renderPoints.emplace_back(i * xSteps, close + j, '#');
      } else {
        if (j == abs(open - close) - 1) {
          renderPoints.emplace_back(i * xSteps, open + j, '^');
          continue;
        }
        renderPoints.emplace_back(i * xSteps, open + j, '#');
      }
    }

    if (open == close) {
      renderPoints.emplace_back(i * xSteps, close, '#');
    }
  }

  return renderPoints;
}

vector<RenderPoint> Graph::renderAxes(const Canvas &canvas) const {
  vector<RenderPoint> renderPoints{};

  int width = canvas.getWidth();
  int height = canvas.getHeight();

  int ySteps = floor(height / this->graphParameters->getY());
  int xSteps = floor(width / this->graphParameters->getX());

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

  for (int i = 0; i < height + Y_THRESHOLD; ++i) {
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
