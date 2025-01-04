#include <mutex>

using namespace std;

enum class EnvType { DEV, PROD };

class Logger {
public:
  Logger &operator=(const Logger &) = delete;
  Logger(Logger &other) = delete;
  Logger(const Logger&) = delete;

  static Logger *getInstance(EnvType env);
  ~Logger() = default;


  void log(const string &message);

private:
  explicit Logger(EnvType _env) : env(_env) {};
  static mutex mutex_;
  static Logger *instance;

  EnvType env;
};

