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

#ifndef ENEMY_H
#define ENEMY_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>

class Enemy: public game::Entity {


public:
  Enemy(b2World &b2_world, game::EventManager& events, sf::Vector2f position);

  Enemy(const Enemy&) = delete;
  Enemy& operator=(const Enemy&) = delete;

  Enemy(Enemy&&) = delete;
  Enemy& operator=(Enemy&&) = delete;

  virtual ~Enemy();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onCharacterLocationEvent(game::EventType type, game::Event *event);

  static constexpr float ENEMY_WIDTH = 10.0f;
    
private:
  b2Body *m_body;
  b2Vec2 m_target;
};

#endif //ENEMY_H
