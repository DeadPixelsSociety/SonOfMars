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
#include "Clock.h"

namespace game {

  Time::Time()
    : m_duration(0) {
  }

  float Time::asSeconds() const {
    return std::chrono::duration_cast<std::chrono::duration<float>>(m_duration).count();
  }

  int32_t Time::asMilliseconds() const {
    return std::chrono::duration_cast<std::chrono::duration<int32_t, std::milli>>(m_duration).count();
  }

  int64_t Time::asMicroseconds() const {
    return std::chrono::duration_cast<std::chrono::duration<int64_t, std::micro>>(m_duration).count();
  }

  Time::Time(std::chrono::steady_clock::duration duration)
    : m_duration(duration) {
  }

  Clock::Clock()
    : m_start(std::chrono::steady_clock::now()) {
  }

  Time Clock::getElapsedTime() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = now - m_start;
    return Time(duration);
  }

  Time Clock::restart() {
    auto now = std::chrono::steady_clock::now();
    auto duration = now - m_start;
    m_start = now;
    return Time(duration);
  }

}




