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

#include "EnemyManager.h"

#include "Game.h"

EnemyManager::EnemyManager(b2World &b2_world, game::EventManager& events)
: m_b2_world(b2_world)
, m_events(events) {
  // Register event
  events.registerHandler<SpawnMobEvent>(&EnemyManager::onSpawnMobEvent, this);
  events.registerHandler<CharacterLocationEvent>(&EnemyManager::onCharacterLocationEvent, this);
}

EnemyManager::~EnemyManager() {
  for (auto enemy : m_enemies) {
    delete enemy;
  }
}

void EnemyManager::update(const float dt) {
  // Define tactics
  // Sort the vector
  std::sort(m_enemies.begin(), m_enemies.end(), [](Enemy* a, Enemy* b) {
    return b->distanceFromCharacter() > a->distanceFromCharacter();
  });

  for (auto enemy : m_enemies) {
    if (enemy->isAlive()) {
      enemy->update(dt);
    }
  }
}

void EnemyManager::render(sf::RenderWindow& window) {
  for (auto enemy : m_enemies) {
    if (enemy->isAlive()) {
      enemy->render(window);
    }
  }
}

game::EventStatus EnemyManager::onSpawnMobEvent(game::EventType type, game::Event *event) {
  auto spawnEvent = static_cast<SpawnMobEvent *>(event);

  m_enemies.push_back(new Enemy(m_b2_world, m_events, spawnEvent->pos, spawnEvent->multiplier));

  return game::EventStatus::KEEP;
}

game::EventStatus EnemyManager::onCharacterLocationEvent(game::EventType type, game::Event *event) {
  auto locationEvent = static_cast<CharacterLocationEvent *>(event);

  b2Vec2 target = locationEvent->pos;
  for (auto enemy : m_enemies) {
    if (enemy->isAlive()) {
      enemy->setCharacterLocation(target);
    }
  }

  return game::EventStatus::KEEP;
}
