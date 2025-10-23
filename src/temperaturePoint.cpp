#include "../include/temperaturePoint.h"
#include "../include/fileReader.h"
#include "../include/logger.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <utility>

const std::unordered_map<string, EULocation> stringToLocationsMap = {
    {"Austria", EULocation::at},        {"Belgium", EULocation::be},
    {"Bulgaria", EULocation::bg},       {"Switzerland", EULocation::ch},
    {"Czech Republic", EULocation::cz}, {"Germany", EULocation::de},
    {"Denmark", EULocation::dk},        {"Estonia", EULocation::ee},
    {"Spain", EULocation::es},          {"Finland", EULocation::fi},
    {"France", EULocation::fr},         {"United Kingdom", EULocation::gb},
    {"Greece", EULocation::gr},         {"Croatia", EULocation::hr},
    {"Hungary", EULocation::hu},        {"Ireland", EULocation::ie},
    {"Italy", EULocation::it},          {"Lithuania", EULocation::lt},
    {"Luxembourg", EULocation::lu},     {"Latvia", EULocation::lv},
    {"Netherlands", EULocation::nl},    {"Norway", EULocation::no},
    {"Poland", EULocation::pl},         {"Portugal", EULocation::pt},
    {"Romania", EULocation::ro},        {"Sweden", EULocation::se},
    {"Slovenia", EULocation::si},       {"Slovakia", EULocation::sk}};

string LocationEnumProcessor::locationToString(EULocation location) {
  auto it = find_if(stringToLocationsMap.begin(), stringToLocationsMap.end(),
                    [location](const pair<string, EULocation> &pair) {
                      return pair.second == location;
                    });

  if (it != stringToLocationsMap.end())
    return it->first;

  throw invalid_argument("Invalid EULocation enum value");
}

EULocation LocationEnumProcessor::stringToLocation(const std::string &country) {
  auto it = stringToLocationsMap.find(country);
  if (it != stringToLocationsMap.end())
    return it->second;

  throw std::invalid_argument("Invalid country name");
}

TemperaturePoint::TemperaturePoint(EULocation _location, float _temperature,
                                   string _date)
    : location(_location), temperature(_temperature), date(_date) {}

vector<TemperaturePoint>
TemparatureDataExtractor::getTemperatures(const string &path) {
  vector<TemperaturePoint> points{};
  vector<string> rows = FileReader::read_file(path);

  for (u_int i = 1; i < rows.size(); ++i) {
    const string &row = rows[i];
    vector<string> tokens = FileReader::tokenise(row, ',');
    string date = tokens[0];

    for (u_int i = 1; i < tokens.size(); i += 3) {
      EULocation location = EULocation::uknown;
      float temperature = -273.15;

      temperature = stof(tokens[i]);
      location = static_cast<EULocation>(floor(i / 3));

      points.emplace_back(location, temperature, date);
    }
  }

  return points;
}

void TemperaturePointsState::setData(const vector<TemperaturePoint> &_points) {
  this->points = vector<TemperaturePoint>(_points);
}

const vector<TemperaturePoint> &TemperaturePointsState::getData() {
  return this->points;
}
