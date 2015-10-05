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
#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <string>

#include <SFML/Window.hpp>

namespace game {

  /**
   * @brief A physical control.
   *
   * @ingroup graphics
   */
  class Control {
  public:
    /**
     * @brief Construct a control with a name and its controller name.
     *
     * @param name the name of the control.
     * @param controller_name the name of the controller
     */
    Control(std::string name, std::string controller_name)
      : m_name(std::move(name))
      , m_controller_name(std::move(controller_name))
      , m_active(false) {
    }

    /**
     * @brief Destroy the control.
     */
    virtual ~Control();

    /**
     * @brief Tell whether the control is active.
     *
     * @return true if the control is active.
     *
     * @sa Action::isActive()
     */
    bool isActive() {
      return m_active;
    }

    /**
     * @brief Change the active state of the control.
     *
     * @param active the new state of the control.
     */
    void setActive(bool active = true) {
      m_active = active;
    }

    /**
     * @brief Desactivate the control.
     *
     * This call is equivalent to:
     *
     * ~~~{.cc}
     *   setActive(false);
     * ~~~
     *
     * @sa Action::reset()
     */
    void reset() {
      m_active = false;
    }

    /**
     * @brief Update the state of the control thanks to an event.
     *
     * @param event the event to update the control.
     *
     * @sa Action::update()
     */
    virtual void update(const sf::Event& event) = 0;

  private:
    const std::string m_name;
    const std::string m_controller_name;
    bool m_active;
  };

  /**
   * @brief A gamepad axis direction.
   *
   * @ingroup graphics
   */
  enum class Direction {
    POSITIVE, ///< Positive direction of the axis.
    NEGATIVE, ///< Negative direction of the axis.
  };

  /**
   * @brief A gamepad axis control.
   *
   * @ingroup graphics
   */
  class GamepadAxisControl : public Control {
  public:
    /**
     * @brief Construct a gamepad axis control.
     *
     * @param id the id of the gamepad.
     * @param axis the axis of the gamepad.
     * @param dir the direction of the axis of the gamepad.
     */
    GamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir);

    virtual void update(const sf::Event& event) override;

  private:
    const unsigned int m_id;
    const sf::Joystick::Axis m_axis;
    const Direction m_dir;
  };

  /**
   * @brief A gamepad button control.
   *
   * @ingroup graphics
   */
  class GamepadButtonControl : public Control {
  public:
    /**
     * @brief Construct a gamepad button control
     *
     * @param id the id of the gamepad
     * @param button the button of the gamepad
     */
    GamepadButtonControl(unsigned int id, unsigned int button);

    virtual void update(const sf::Event& event) override;

  private:
    const unsigned int m_id;
    const unsigned int m_button;
  };

  /**
   * @brief A key control.
   *
   * @ingroup graphics
   */
  class KeyControl : public Control {
  public:
    /**
     * @brief Construct a key control.
     *
     * @param key the key of the keyboard.
     */
    KeyControl(sf::Keyboard::Key key);

    virtual void update(const sf::Event& event) override;

  private:
    const sf::Keyboard::Key m_key;
  };

  /**
   * @brief A mouse button control.
   *
   * @ingroup graphics
   */
  class MouseButtonControl : public Control {
  public:
    /**
     * @brief Construct a mouse button control.
     *
     * @param button the button of the mouse.
     */
    MouseButtonControl(sf::Mouse::Button button);

    virtual void update(const sf::Event& event) override;

  private:
    sf::Mouse::Button m_button;
  };

  /**
   * @brief A close control.
   *
   * @ingroup graphics
   */
  class CloseControl : public Control {
  public:
    /**
     * @brief Construct a close control.
     */
    CloseControl();

    virtual void update(const sf::Event& event) override;
  };

}

#endif // GAME_CONTROL_H
