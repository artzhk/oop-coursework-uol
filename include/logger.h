#pragma once
#include "timing.h"
#include <chrono>
#include <mutex>
#include <string>
#include <thread>

#ifndef LOG_LEVEL
#define LOG_LEVEL 3
#endif
#ifndef LOG_FLUSH
#define LOG_FLUSH 1
#endif

namespace slog {
enum level { PROD = 0, ERROR = 1, INFO = 2, DEBUG = 3 };

inline std::mutex &mtx() {
  static std::mutex m;
  return m;
}

inline size_t tid() {
  return std::hash<std::thread::id>{}(std::this_thread::get_id());
}

inline void vprint(level lvl, const char *tag, const char *file, int line,
                   const char *func, const char *fmt, va_list ap) {
#if LOG_LEVEL >= 1
  if (lvl > LOG_LEVEL)
    return;
  std::lock_guard<std::mutex> lk(mtx());
  std::fprintf(stdout, "%llu [%s] [t=%zu] %s:%d %s: ", timing::elapsedMs(), tag,
               tid(), file, line, func);
  std::vfprintf(stdout, fmt, ap);
  std::fputc('\n', stdout);
#if LOG_FLUSH
  std::fflush(stdout);
#endif
#else
  // supress -Wunused based on
  // https://gcc.gnu.org/onlinedocs/gcc-3.1/gcc/Warning-Options.html
  (void)lvl;
  (void)tag;
  (void)file;
  (void)line;
  (void)func;
  (void)fmt;
#endif
}

inline void print(level lvl, const char *tag, const char *file, int line,
                  const char *func, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vprint(lvl, tag, file, line, func, fmt, ap);
  va_end(ap);
}
} // namespace slog

#define LOG_INFO(...)                                                          \
  do {                                                                         \
    ::slog::print(::slog::INFO, "INFO", __FILE__, __LINE__, __func__,          \
                  __VA_ARGS__);                                                \
  } while (0)
#define LOG_OK(...)                                                            \
  do {                                                                         \
    ::slog::print(::slog::INFO, "OK", __FILE__, __LINE__, __func__,            \
                  __VA_ARGS__);                                                \
  } while (0)
#define LOG_FAIL(...)                                                          \
  do {                                                                         \
    ::slog::print(::slog::ERROR, "FAIL", __FILE__, __LINE__, __func__,         \
                  __VA_ARGS__);                                                \
  } while (0)
#define LOG_DBG(...)                                                           \
  do {                                                                         \
    ::slog::print(::slog::DEBUG, "DEBUG", __FILE__, __LINE__, __func__,        \
                  __VA_ARGS__);                                                \
  } while (0)
