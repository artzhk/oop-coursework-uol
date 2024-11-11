#include "./file_reader.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> FileReader::read_file(string path) {
  ifstream csv_file{path};
  vector<string> lines;
  string *line = nullptr;

  while (getline(csv_file, *line)) {
    if (csv_file.is_open()) {
      lines.push_back(*line);
    }
  }

  csv_file.close();

  return lines;
}
