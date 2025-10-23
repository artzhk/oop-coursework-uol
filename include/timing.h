#pragma once
#include <chrono>

namespace timing {
using clock = std::chrono::steady_clock;

inline uint64_t elapsed_ms() {
  static const clock::time_point t0 = clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() -
                                                               t0)
      .count();
}
} // namespace timing
