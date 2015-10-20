/*
 * Son of Mars
 *
 * Copyright (c) 2015-2016, Team Son of Mars
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>

#include <cmath>

#define _USE_MATH_DEFINES

class Character: public game::Entity {

	
public:
  enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE,
  };

public:
  Character(b2World &b2_world);

  Character(const Character&) = delete;
  Character& operator=(const Character&) = delete;

  Character(Character&&) = delete;
  Character& operator=(Character&&) = delete;

  virtual ~Character();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  // Events
  void move(Direction direction);
  void setTarget(sf::Vector2f mousePos);

  static constexpr float CHARACTER_WIDTH = 10.0f;
    
private:
  b2Body *m_body;
  Direction m_verticalDirection;
  Direction m_horizontalDirection;

  b2Vec2 m_target;
};

#endif //CHARACTER_H
