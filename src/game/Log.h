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
#ifndef GAME_LOG_H
#define GAME_LOG_H

#include <cstdarg>
#include <cstdlib>
#include <map>

namespace game {
  /**
   * @ingroup base
   */
  class Log {
  public:
    Log() = delete;

    enum Level : int {
      DEBUG,
      INFO,
      WARN,
      ERROR,
      FATAL,
    };

    enum Category : int {
      GENERAL,
      GRAPHICS,
      NETWORK,
      PHYSICS,
      RESOURCES,
    };

    static void setLevel(Level level);

    static void setLevel(Category category, Level level);

    static void debug(Category category, const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::DEBUG, category, fmt, ap);
      va_end(ap);
    }

    static void info(Category category, const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::INFO, category, fmt, ap);
      va_end(ap);
    }

    static void warning(Category category, const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::WARN, category, fmt, ap);
      va_end(ap);
    }

    static void error(Category category, const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::ERROR, category, fmt, ap);
      va_end(ap);
    }

    static void fatal(Category category, const char *fmt, ...) {
      va_list ap;
      va_start(ap, fmt);
      log(Level::FATAL, category, fmt, ap);
      va_end(ap);

      std::abort();
    }

  private:
    static void log(Level level, Category category, const char *fmt, va_list ap);

  private:
    static std::map<Category, Level> s_levels;
  };

}

#endif // GAME_LOG_H
