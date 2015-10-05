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
#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include <memory>
#include <vector>

#include "Control.h"

namespace game {

  /**
   * @brief An action that can be triggered by different controls.
   *
   * @ingroup graphics
   */
  class Action {
  public:
    /**
     * @brief Construct an action with a name.
     *
     * @param name the name of the action.
     */
    Action(std::string name);

    /**
     * @brief Get the name of the action.
     *
     * @return the name of the action.
     */
    const std::string& getName() const {
      return m_name;
    }


    /**
     * @name Type of the action
     * @{
     */
    /**
     * @brief Set the action continuous.
     *
     * A continuous action is an action that is active as long as the user do
     * not desactivate it. A reset() call does not desactivate the action.
     *
     * @sa reset(), setInstantaneous()
     */
    void setContinuous();

    /**
     * @brief Tell whether the action is continuous.
     *
     * @return true if the action is continuous.
     */
    bool isContinuous() const;

    /**
     * @brief Set the action instantaneous.
     *
     * An instantaneous action is an action that is active until the next
     * reset() call.
     *
     * @sa reset(), setContinuous()
     */
    void setInstantaneous();

    /**
     * @brief Tell whether the action is instantaneous.
     *
     * @return true if the action is instantaneous.
     */
    bool isInstantaneous() const;
    /** @} */

    /**
     * @name Controls for the action
     * @{
     */
    /**
     * @brief Add a gamepad axis control.
     *
     * @param id the id of the gamepad.
     * @param axis the axis of the gamepad.
     * @param dir the direction of the axis of the gamepad.
     *
     * @sa GamepadAxisControl
     */
    void addGamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir);

    /**
     * @brief Add a gamepad button control.
     *
     * @param id the id of the gamepad.
     * @param button the button of the gamepad
     *
     * @sa GamepadButtonControl
     */
    void addGamepadButtonControl(unsigned int id, unsigned int button);

    /**
     * @brief Add a key control.
     *
     * @param key the key of the keyboard.
     *
     * @sa KeyControl
     */
    void addKeyControl(sf::Keyboard::Key key);

    /**
     * @brief Add a mouse button control.
     *
     * @param button the button of the mouse.
     *
     * @sa MouseButtonControl
     */
    void addMouseButtonControl(sf::Mouse::Button button);

    /**
     * @brief Add a close control.
     *
     * @sa CloseControl
     */
    void addCloseControl();
    /** @} */

    /**
     * @name State of the action
     * @{
     */
    /**
     * @brief Update the state of the action thanks to an event.
     *
     * @param event the event to update the action.
     *
     * @sa Control::update()
     */
    void update(const sf::Event& event);

    /**
     * @brief Tell whether the action is active.
     *
     * An action is active if at least one of its control is active.
     *
     * @return true if the action is active.
     *
     * @sa Control::isActive()
     */
    bool isActive();

    /**
     * @brief Reset the state of the action.
     *
     * This function depends of the type of the action.
     *
     * @sa setContinuous(), setInstantaneous(), Control::reset()
     */
    void reset();
    /** @} */

  private:
    enum class Type {
      INSTANTANEOUS,
      CONTINUOUS,
    };

    const std::string m_name;
    Type m_type;
    std::vector<std::unique_ptr<Control>> m_controls;
  };

  /**
   * @brief A set of actions.
   *
   * @ingroup graphics
   */
  class ActionManager {
  public:
    /**
     * @brief Add an action.
     *
     * @param action the action to add to the set.
     */
    void addAction(Action& action);

    /**
     * @brief Update all the actions.
     *
     * @param event the event to update the actions.
     *
     * @sa Action;:update()
     */
    void update(const sf::Event& event);

    /**
     * @brief Reset all the actions.
     *
     * @sa Action::reset()
     */
    void reset();

  private:
    std::vector<Action*> m_actions;
  };

}

#endif // GAME_ACTION_H
