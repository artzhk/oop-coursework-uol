#pragma once
#include <mutex>
#include <string>
#include <chrono>

enum class EnvType { DEV, PROD };

class Logger {
public:
  Logger &operator=(const Logger &) = delete;
  Logger(Logger &other) = delete;
  Logger(const Logger &) = delete;

  static Logger *getInstance(EnvType env);
  ~Logger() = default;

  void log(const std::string &message);

private:
  explicit Logger(EnvType _env) : env(_env) {};
  static std::mutex mutex_;
  static Logger *instance;

  EnvType env;
};

