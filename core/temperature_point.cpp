#include "./temperature_point.h"
#include "../utils/file_reader.h"
#include <sys/types.h>

TemperaturePoint::TemperaturePoint(eu_location _location, float _temperature, string _date) : 
    location(_location), temperature(_temperature), date(_date) {}

vector<TemperaturePoint> TemparatureDataExtractor::get_temperature_data(const string &path) {
    vector<TemperaturePoint> points{};
    vector<string> rows = FileReader::read_file(path);
    TemperaturePoint *point = new TemperaturePoint(eu_location::at, 0.0, "error");

    for(const string &row : rows) {
        vector<string> tokens = FileReader::tokenise(row, ',');

        for (u_int i = 0; i < tokens.size(); ++i) {
            TemperaturePoint *point 
        }
    }

    

    return points;
}
