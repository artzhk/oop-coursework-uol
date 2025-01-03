#include "graph.h"
#include "../../utils/logger.h"
#include <string>

#define Y_THRESHOLD 5
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

  float min = CandlestickProcessor::getLowest(vector<Candlestick>{
      this->candlesticks.begin(), this->candlesticks.begin() + pagination});
  float max = CandlestickProcessor::getHighest(vector<Candlestick>{
      this->candlesticks.begin(), this->candlesticks.begin() + pagination});
  int tempStep = float((max - min) / 10);

  for (int i = 0; i * xSteps < width && i < size; ++i) {
    const Candlestick &candlestick = this->candlesticks[i];

    for (int j = 0; j < floor(candlesticks[i].date.size() - 7); ++j) {
      renderPoints.emplace_back((i * xSteps) + j, floor(height / 2) - 1,
                                candlesticks[i].date[j]);
    }
  }

  for (int i = 0; i * ySteps < height && i < size; ++i) {
    const Candlestick &candlestick = this->candlesticks[i];

    const string temp = to_string(candlestick.close);
    logger->log("TEMP: " + temp);
    for (int j = 3; j > 0; --j) {
      renderPoints.emplace_back(Y_THRESHOLD - j, i * ySteps, temp[3 - j]);
    }
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

  for (int i = 5; i < width; ++i) {
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

  for (int i = height; i > 0; --i) {
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
