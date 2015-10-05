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
#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include <cstdint>
#include <chrono>

namespace game {

  /**
   * @ingroup base
   */
  class Time {
  public:
    Time();

    float asSeconds() const;
    int32_t asMilliseconds() const;
    int64_t asMicroseconds() const;

  private:
    friend class Clock;

    explicit Time(std::chrono::steady_clock::duration duration);

    std::chrono::steady_clock::duration m_duration;
  };

  /**
   * @ingroup base
   */
  class Clock {
  public:
    Clock();

    Time getElapsedTime() const;
    Time restart();

  private:
    std::chrono::steady_clock::time_point m_start;
  };

}

#endif // GAME_CLOCK_H
