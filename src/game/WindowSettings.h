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
#ifndef GAME_WINDOW_SETTINGS_H
#define GAME_WINDOW_SETTINGS_H

#include <string>

#include <SFML/Window.hpp>

namespace game {

  /**
   * @ingroup graphics
   */
  class WindowSettings {
  public:
    WindowSettings(unsigned initial_width, unsigned initial_height, std::string title)
    : m_mode(initial_width, initial_height)
    , m_title(std::move(title))
    , m_fullscreen(false)
    {
      m_settings.antialiasingLevel = 8;
    }

    void toggleFullscreen();
    void applyTo(sf::Window& window);

  private:
    sf::VideoMode m_mode;
    std::string m_title;
    bool m_fullscreen;
    sf::ContextSettings m_settings;
  };

}


#endif // GAME_WINDOW_SETTINGS_H
