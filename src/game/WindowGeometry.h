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
#ifndef GAME_WINDOW_GEOMETRY_H
#define GAME_WINDOW_GEOMETRY_H

#include <SFML/Graphics.hpp>

namespace game {

  class WindowGeometry {
  public:
    WindowGeometry(float width, float height)
    : m_width(width)
    , m_height(height)
    {

    }

    void update(sf::Event& event);

    float getXCentered(float width);
    float getXFromRight(float width);
    float getXRatio(float r, float width);

    float getYCentered(float height);
    float getYFromBottom(float height);
    float getYRatio(float r, float height);

    sf::Vector2f getCornerPosition(const sf::Vector2f& pos);

  private:
    float m_width;
    float m_height;
  };

}

#endif // GAME_WINDOW_GEOMETRY_H
