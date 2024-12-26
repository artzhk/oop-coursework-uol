#include "./temperature_point.h"
#include "../utils/file_reader.h"
#include <cmath>
#include <string>
#include <sys/types.h>

TemperaturePoint::TemperaturePoint(EULocation _location, float _temperature,
                                   string _date)
    : location(_location), temperature(_temperature), date(_date) {}

vector<TemperaturePoint>
TemparatureDataExtractor::getTemperatures(const string &path) {
  vector<TemperaturePoint> points{};
  vector<string> rows = FileReader::read_file(path);

  for (const string &row : rows) {
    vector<string> tokens = FileReader::tokenise(row, ',');

    for (u_int i = 0; i < tokens.size(); ++i) {
      EULocation location = EULocation::uknown;
      float temperature = -273.15;
      string date = tokens[i];

      // Need to be tested
      if (i % 3 == 1) {
        temperature = stof(tokens[i]);
        location = static_cast<EULocation>(floor(i / 3));
      }

      points.emplace_back(location, temperature, date);
    }
  }

  return points;
}

void TemperaturePointsState::setData(const vector<TemperaturePoint> &_points) {
  this->points = unique_ptr<vector<TemperaturePoint>>(
      new vector<TemperaturePoint>(_points));
}

const vector<TemperaturePoint> &TemperaturePointsState::getData() {
  return *this->points;
}
