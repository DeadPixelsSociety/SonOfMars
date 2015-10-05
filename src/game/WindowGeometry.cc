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
#include "WindowGeometry.h"

namespace game {

  void WindowGeometry::update(sf::Event& event) {
    if (event.type != sf::Event::Resized) {
      return;
    }

    m_width = static_cast<float>(event.size.width);
    m_height = static_cast<float>(event.size.height);
  }

  float WindowGeometry::getXCentered(float w) {
    return m_width / 2 - w / 2;
  }

  float WindowGeometry::getXFromRight(float x) {
    return m_width - x;
  }


  float WindowGeometry::getYCentered(float h) {
    return m_height / 2 - h / 2;
  }

  float WindowGeometry::getYFromBottom(float y) {
    return m_height - y;
  }

  sf::Vector2f WindowGeometry::getCornerPosition(const sf::Vector2f& pos) {
    float x = pos.x > 0 ? pos.x : m_width + pos.x;
    float y = pos.y > 0 ? pos.y : m_height + pos.y;
    return { x, y };
  }

}
