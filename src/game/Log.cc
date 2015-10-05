/*
 * Copyright (c) 2014-2015, Julien Bernard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include "Log.h"

#include <cassert>
#include <ctime>

namespace game {

  // default values
  std::map<Log::Category, Log::Level> Log::s_levels = {
    { Log::GENERAL, Log::WARN },
    { Log::GRAPHICS, Log::WARN },
    { Log::NETWORK, Log::WARN },
    { Log::PHYSICS, Log::WARN },
    { Log::RESOURCES, Log::WARN },
  };

  void Log::setLevel(Level level) {
    for (auto& item : s_levels) {
      item.second = level;
    }
  }

  void Log::setLevel(Category category, Level level) {
    s_levels[category] = level;
  }

  static const char *levelToString(Log::Level level) {
    switch (level) {
      case Log::DEBUG:
        return "DEBUG";

      case Log::INFO:
        return "INFO";

      case Log::WARN:
        return "WARN";

      case Log::ERROR:
        return "ERROR";

      case Log::FATAL:
        return "FATAL";
    }

    assert(false);
    return "?";
  }

  static const char *categoryToString(Log::Category category) {
    switch (category) {
      case Log::GENERAL:
        return "GENERAL";

      case Log::GRAPHICS:
        return "GRAPHICS";

      case Log::NETWORK:
        return "NETWORK";

      case Log::PHYSICS:
        return "PHYSICS";

      case Log::RESOURCES:
        return "RESOURCES";
    }

    assert(false);
    return "?";
  }

  void Log::log(Level level, Category category, const char *fmt, va_list ap) {
    if (level < s_levels[category]) {
      return;
    }

    unsigned long t = std::time(nullptr);
    std::fprintf(stderr, "[%lu][%s][%s] ", t, levelToString(level), categoryToString(category));

    std::vfprintf(stderr, fmt, ap);
  }

}
