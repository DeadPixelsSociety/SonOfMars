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
#include "Random.h"

#include <ctime>

namespace game {

  Random::Random()
    : m_engine(std::time(nullptr)) {

  }

  Random::Random(unsigned seed)
    : m_engine(seed) {

  }


  int Random::computeUniformInteger(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
  }

  float Random::computeUniformFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine);
  }

  float Random::computeNormalFloat(float mean, float stddev) {
    std::normal_distribution<float> dist(mean, stddev);
    return dist(m_engine);
  }

  bool Random::computeBernoulli(float p) {
    std::bernoulli_distribution dist(p);
    return dist(m_engine);
  }
}
