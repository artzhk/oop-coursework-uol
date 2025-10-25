#include "../../include/logger.h"
#include <iostream>
#include "../../include/timing.h"

Logger *Logger::instance = nullptr;

Logger *Logger::getInstance(EnvType env) {
  if (instance == nullptr) {
    instance = new Logger(env);
  }
  return instance;
}

void Logger::log(const std::string &message) {
  if (env == EnvType::PROD) {
    return;
  }

  uint64_t ms = timing::elapsed_ms();
  std::cout << "[" << ms << "]" << "[LOG]:" << message << std::endl;
  return;
}
