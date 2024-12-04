#include <string>
#include <vector>

using namespace std;

class FileReader {
private:
public:
  static vector<string> read_file(string path);
  static vector<string> *tokenise(string *csvLine, char separator);
};
