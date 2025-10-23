#pragma once
#include <string>
#include <vector>

class FileReader {
private:
public:
  static std::vector<std::string> read_file(const std::string &path);
  static std::vector<std::string> tokenise(const std::string &csvLine,
                                           char separator);
  static bool exists(const std::string &name);
};
