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
#include "Animation.h"

#include <iostream>

#include "Log.h"

namespace game {

  void Animation::addFrame(sf::Texture *texture, const sf::IntRect& bounds, float duration) {
    if (texture == nullptr) {
      Log::error(Log::GRAPHICS, "The frame does not have any texture: %s\n", m_name.c_str());
      return;
    }

    if (m_frames.empty()) {
      m_current_duration_in_frame = duration;
      m_current_frame = 0;
    }

    m_frames.push_back({ texture, bounds, duration });
  }

  void Animation::update(float dt) {
    if (m_frames.empty()) {
      return;
    }

    m_current_duration_in_frame -= dt;

    while (m_current_duration_in_frame < 0) {
      m_current_frame = (m_current_frame + 1) % m_frames.size();
      m_current_duration_in_frame += m_frames[m_current_frame].duration;
    }
  }

  void Animation::renderAt(sf::RenderWindow& window, const sf::Vector2f& position, float angle) const {
    if (m_frames.empty()) {
      Log::error(Log::GRAPHICS, "The animation does not have any frame: %s\n", m_name.c_str());
      return;
    }

    const Frame& frame = m_frames[m_current_frame];
    sf::Sprite sprite(*frame.texture, frame.bounds);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width * 0.5, bounds.height * 0.5);

    sprite.setPosition(position);
    sprite.setRotation(angle);
    window.draw(sprite);
  }

}
