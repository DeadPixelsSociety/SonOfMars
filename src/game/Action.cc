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
#include "Action.h"

#include <cassert>

namespace game {

  Action::Action(std::string name)
    : m_name(std::move(name))
    , m_type(Type::INSTANTANEOUS) {
  }

  void Action::setContinuous() {
    m_type = Type::CONTINUOUS;
  }

  bool Action::isContinuous() const {
    return m_type == Type::CONTINUOUS;
  }

  void Action::setInstantaneous() {
    m_type = Type::INSTANTANEOUS;
  }

  bool Action::isInstantaneous() const {
    return m_type == Type::INSTANTANEOUS;
  }

  void Action::addGamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir) {
    std::unique_ptr<Control> ptr(new GamepadAxisControl(id, axis, dir));
    m_controls.push_back(std::move(ptr));
  }

  void Action::addGamepadButtonControl(unsigned int id, unsigned int button) {
    std::unique_ptr<Control> ptr(new GamepadButtonControl(id, button));
    m_controls.push_back(std::move(ptr));
  }

  void Action::addKeyControl(sf::Keyboard::Key key) {
    std::unique_ptr<Control> ptr(new KeyControl(key));
    m_controls.push_back(std::move(ptr));
  }

  void Action::addMouseButtonControl(sf::Mouse::Button button) {
    std::unique_ptr<Control> ptr(new MouseButtonControl(button));
    m_controls.push_back(std::move(ptr));
  }

  void Action::addCloseControl() {
    std::unique_ptr<Control> ptr(new CloseControl);
    m_controls.push_back(std::move(ptr));
  }

  void Action::update(const sf::Event& event) {
    for (auto& control : m_controls) {
      control->update(event);
    }
  }

  bool Action::isActive() {
    for (auto& control : m_controls) {
      if (control->isActive()) {
        return true;
      }
    }

    return false;
  }

  void Action::reset() {
    if (isContinuous()) {
      return;
    }

    for (auto& control : m_controls) {
      control->reset();
    }
  }

  // ActionManager

  void ActionManager::addAction(Action& action) {
    m_actions.push_back(&action);
  }

  void ActionManager::update(const sf::Event& event) {
    for (auto action : m_actions) {
      action->update(event);
    }
  }

  void ActionManager::reset() {
    for (auto action : m_actions) {
      action->reset();
    }
  }

}
