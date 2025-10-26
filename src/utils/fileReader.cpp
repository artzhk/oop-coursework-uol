#include "../../include/fileReader.h"
#include <fstream>
#include <iostream>

std::vector<std::string> FileReader::read_file(const std::string &path) {
  std::ifstream csv_file{path};
  std::vector<std::string> lines;
  std::string line;

  if (csv_file.is_open()) {
    while (true) {
      if (!getline(csv_file, line)) {
        break;
      }
      lines.push_back(line);
    }
    csv_file.close();
  }

  return lines;
}

std::vector<std::string> FileReader::tokenise(const std::string &csv_line,
                                              char separator) {
  std::vector<std::string> tokens{};
  signed int start, end;
  start = csv_line.find_last_not_of(separator, 0);

  std::string token;

  do {
    end = csv_line.find_first_of(separator, start);
    if (end >= 0) {
      token = csv_line.substr(start, end - start);
    } else {
      token = csv_line.substr(start, csv_line.length() - start);
    }

    tokens.push_back(token);
    start = end + 1;
  } while (end > 0);

  return tokens;
}

bool FileReader::exists(const std::string &name) {
  std::ifstream f(name.c_str());
  return f.good();
}
