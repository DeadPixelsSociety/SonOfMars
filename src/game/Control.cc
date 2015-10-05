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
#include "Control.h"

#include <cassert>

namespace game {

  // control

  Control::~Control() {
  }


  // gamepad axis control

  static const char *axisName(sf::Joystick::Axis axis) {
    return "?";
  }

  GamepadAxisControl::GamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir)
    : Control("gamepad (axis)", axisName(axis))
    , m_id(id)
    , m_axis(axis)
    , m_dir(dir) {
  }

  void GamepadAxisControl::update(const sf::Event& event) {
    if (event.type == sf::Event::JoystickMoved) {
      if (event.joystickMove.joystickId == m_id && event.joystickMove.axis == m_axis) {
        switch (m_dir) {
          case Direction::POSITIVE:
            setActive(event.joystickMove.position > 50.0f);
            break;
          case Direction::NEGATIVE:
            setActive(event.joystickMove.position < -50.0f);
            break;
        }
      }
    }
  }


  // gamepad button control

  GamepadButtonControl::GamepadButtonControl(unsigned int id, unsigned int button)
    : Control("gamepad (button)", std::to_string(button))
    , m_id(id)
    , m_button(button) {
  }

  void GamepadButtonControl::update(const sf::Event& event) {
    if (event.type == sf::Event::JoystickButtonPressed) {
      if (event.joystickButton.joystickId == m_id && event.joystickButton.button == m_button) {
        setActive();
      }
    }

    if (event.type == sf::Event::JoystickButtonReleased) {
      if (event.joystickButton.joystickId == m_id && event.joystickButton.button == m_button) {
        setActive(false);
      }
    }
  }


  // key control

  static const char *keyName(sf::Keyboard::Key key) {
    return "?";
  }

  KeyControl::KeyControl(sf::Keyboard::Key key)
    : Control("keyboard", keyName(key))
    , m_key(key) {

  }

  void KeyControl::update(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == m_key) {
        setActive();
      }
    }

    if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == m_key) {
        setActive(false);
      }
    }
  }


  // mouse button control

  const char *buttonName(sf::Mouse::Button button) {
    return "?";
  }

  MouseButtonControl::MouseButtonControl(sf::Mouse::Button button)
    : Control("mouse", buttonName(button))
    , m_button(button) {
  }

  void MouseButtonControl::update(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == m_button) {
        setActive();
      }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      if (event.mouseButton.button == m_button) {
        setActive(false);
      }
    }
  }


  // close control

  CloseControl::CloseControl()
    : Control("window", "close") {
  }

  void CloseControl::update(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
      setActive();
    }
  }

}
