#include "./file_reader.h"
#include <fstream>
#include <iostream>

using namespace std;

vector<string> FileReader::read_file(string path) {
  ifstream csv_file{path};
  vector<string> lines;
  string line;

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

vector<string> *FileReader::tokenise(string *csv_line, char separator) {
  vector<string> *tokens = new vector<string>;
  signed int start, end;
  start = csv_line->find_last_not_of(separator, 0);

  string token;

  do {
    end = csv_line->find_first_of(separator, start);
    if (end >= 0) {
      token = csv_line->substr(start, end - start);
    } else {
      token = csv_line->substr(start, csv_line->length() - start);
    }

    tokens->push_back(token);
    start = end + 1;
  } while (end > 0);

  return tokens;
}

