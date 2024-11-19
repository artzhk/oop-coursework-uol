#include <string>
#include <vector>
using namespace std;

vector<string> *tokenise(string *csvLine, char separator) {
  vector<string> *tokens{};
  signed int start, end;
  start = csvLine->find_last_not_of(separator, 0);

  string token;

  do {
    end = (*csvLine).find_first_of(separator, start);
    if (end >= 0) {
      token = csvLine->substr(start, end - start);
    } else {
      token = csvLine->substr(start, csvLine->length() - start);
    }
  } while (true);
}
