#include <string>
#include <vector>

using namespace std;

class FileReader {
private:
public:
  static vector<string> read_file(const string &path);
  static vector<string> tokenise(const string &csvLine, char separator);
};
