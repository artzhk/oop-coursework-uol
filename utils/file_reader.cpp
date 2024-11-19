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


int main() {
  FileReader reader{};
  vector<string *> strings = reader.read_file("../Bird_strikes.csv");
  cout << "Hello" << endl;

  for (string *str : strings) {
    cout << *str << endl;
  }

  return -1;
}
