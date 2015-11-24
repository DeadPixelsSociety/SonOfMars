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

#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <random>
#include <iostream>

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/Random.h>

class Arena: public game::Entity {
public:
  Arena(b2World &b2_world, game::EventManager& events);

  Arena(const Arena&) = delete;
  Arena& operator=(const Arena&) = delete;

  Arena(Arena&&) = delete;
  Arena& operator=(Arena&&) = delete;

  virtual ~Arena();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  void spawnEnemy(game::Random &random);

private:
  game::EventManager& m_events;
  float m_timeElapsed;
  std::vector<b2Body*> m_walls;
  int m_enemyCounter;
  int m_waveNumber;
};

#endif //ARENA_H
