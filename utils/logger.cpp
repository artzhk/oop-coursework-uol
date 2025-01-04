#include "logger.h"
#include <iostream>

Logger *Logger::instance = nullptr;

Logger *Logger::getInstance(EnvType env) {
  if (instance == nullptr) {
    instance = new Logger(env);
  }

  return instance;
}

void Logger::log(const string &message) {
  if (env == EnvType::PROD) {
    return;
  }

  cout << "LOG: " << message << endl;

  return;
}
