#include <string>
#include <vector>

namespace cli {

enum DataType { String, Number, Bool, Object, Enumerator };

struct Param {
  std::string name;
  std::vector<std::string> aliases;
  DataType type = DataType::String;
  bool required = false;
  bool allow_multi = false;
  std::string help;
};

struct Core {
  std::vector<Param> params;
  template <class T> T parse(const std::vector<Param> &schema);
};

} // namespace cli
