#include "./file_reader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string *> FileReader::read_file(string path) {
  ifstream csv_file{path};
  vector<string *> lines;
  string *line = nullptr;

  if (csv_file.is_open()) {
    while (true) {
      line = new string;
      if (!getline(csv_file, *line)) {
        delete line;
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

vector<OrderBookEntry> *
FileReader::read_to_order_book_entry(string path) {
  vector<OrderBookEntry> *entries = new vector<OrderBookEntry>();
  vector<string *> rows = read_file(path);

  for (string *row : rows) {
    vector<string> *tokens = tokenise(row, ',');
    OrderBookEntry entry = new {(*tokens)[0], (*tokens)[1], (*tokens)[2], (*tokens)[3], (*tokens)[4]};
  }

  return
}
