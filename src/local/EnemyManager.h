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

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/Random.h>

#include "Character.h"
#include "Enemy.h"

class EnemyManager: public game::Entity {
public:
  EnemyManager(b2World &b2_world, game::EventManager& events, game::Random &random);

  EnemyManager(const EnemyManager&) = delete;
  EnemyManager& operator=(const EnemyManager&) = delete;

  EnemyManager(EnemyManager&&) = delete;
  EnemyManager& operator=(EnemyManager&&) = delete;

  virtual ~EnemyManager();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onCharacterLocationEvent(game::EventType type, game::Event *event);

private:
  void spawnEnemy();

private:
  std::vector<Enemy*> m_enemies;
  b2World &m_b2_world;
  game::EventManager& m_events;
  game::Random& m_random;
  float m_timeElapsed;
  unsigned m_waveNumber;
  b2Vec2 m_heroPos;
};

#endif // ENEMY_MANAGER_H
