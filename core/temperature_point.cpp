#include "./temperature_point.h"
#include "../utils/file_reader.h"
#include <cmath>
#include <string>
#include <sys/types.h>

TemperaturePoint::TemperaturePoint(eu_location _location, float _temperature, string _date) : 
    location(_location), temperature(_temperature), date(_date) {}

vector<TemperaturePoint> TemparatureDataExtractor::get_temperature_data(const string &path) {
    vector<TemperaturePoint> points{};
    vector<string> rows = FileReader::read_file(path);

    for(const string &row : rows) {
        vector<string> tokens = FileReader::tokenise(row, ',');

        for (u_int i = 0; i < tokens.size(); ++i) {
            eu_location location = eu_location::uknown;
            float temperature = -273.15;
            string date = tokens[i];

            // Need to be tested
            if (i % 3 == 1) {
                temperature = stof(tokens[i]);
                location = static_cast<eu_location>(floor(i / 3));
            }

            points.emplace_back(location, temperature, date);
        }
    }

    return points;
}
