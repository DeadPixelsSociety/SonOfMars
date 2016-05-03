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

#include "Arena.h"
#include "Game.h"
#include "local/config.h"

static constexpr unsigned int SQUAD_NUMBER = 5;

static constexpr float SPAWN_PERIOD = 2.0f;

static constexpr int MIN_ENEMIES_PER_WAVE = 3;
static constexpr int INCREASE_ENEMY_POWER_RATE = 5; // every INCREASE_ENEMY_POWER_RATE, enemies will get more powerful

EnemyManager::EnemyManager(b2World &b2_world, game::EventManager& events, game::Random &random)
: m_b2_world(b2_world)
, m_events(events)
, m_random(random)
, m_timeElapsed(0.0f)
, m_waveNumber(0) {
  // Register event
  events.registerHandler<CharacterLocationEvent>(&EnemyManager::onCharacterLocationEvent, this);
}

EnemyManager::~EnemyManager() {
  for (auto enemy : m_enemies) {
    delete enemy;
  }
}

void EnemyManager::update(const float dt) {
  //Remove the deads
  const auto trash = std::partition(m_enemies.begin(), m_enemies.end(), [](const Enemy *e) {
    return e->isAlive();
  });

  for (auto it = trash; it != m_enemies.end(); ++it) {
    assert(!(*it)->isAlive());
    delete *it;
    *it = nullptr;
  }

  m_enemies.erase(trash, m_enemies.end());

  // Define tactics
  // Sort the vector
  std::sort(m_enemies.begin(), m_enemies.end(), [](Enemy* a, Enemy* b) {
    return b->distanceFromCharacter() > a->distanceFromCharacter();
  });

  // The first 10
  for (unsigned i = 0; i < SQUAD_NUMBER && i < m_enemies.size(); ++i) {
    if (m_enemies[i]->isAlive()) {
      m_enemies[i]->update(dt, Enemy::ActionType::ATTACK);
    }
  }

  // the others
  for (unsigned i = SQUAD_NUMBER; i < m_enemies.size(); ++i) {
    if (m_enemies[i]->isAlive()) {
      m_enemies[i]->update(dt, Enemy::ActionType::CIRCLE);
    }
  }

  // Manage the spawn
  m_timeElapsed += dt;

  // If is the first wave or not the last wave
  if (m_waveNumber == 0 || (m_timeElapsed >= SPAWN_PERIOD && m_waveNumber % 5 != 0)) {
    if (m_waveNumber != 0) {
      m_timeElapsed -= SPAWN_PERIOD;
    }

    m_waveNumber++;

    unsigned numberEnemies = m_random.computeUniformInteger(1, 1);
    for (unsigned i = 0; i < numberEnemies; ++i) {
      // spawnEnemy();
    }
  }

  // If the safe zone needed
  if (m_enemies.size() == 0 && m_waveNumber % 5 == 0) {
    // Trigger teleport event
    EndWaveEvent event;
    m_events.triggerEvent(&event);
  }
}

void EnemyManager::render(sf::RenderWindow& window) {
  for (auto enemy : m_enemies) {
    if (enemy->isAlive()) {
      enemy->render(window);
    }
  }
}

game::EventStatus EnemyManager::onCharacterLocationEvent(game::EventType type, game::Event *event) {
  auto locationEvent = static_cast<CharacterLocationEvent *>(event);

  m_heroPos = locationEvent->pos;
  for (auto enemy : m_enemies) {
    if (enemy->isAlive()) {
      enemy->setCharacterLocation(m_heroPos);
    }
  }

  return game::EventStatus::KEEP;
}

void EnemyManager::spawnEnemy() {
  // Make the new ennemy spawn randomly near one of the corners
  // float multiplier = (m_waveNumber / INCREASE_ENEMY_POWER_RATE) + 1;
  
  // sf::Vector2f heroPos = {m_heroPos.x, m_heroPos.y};
  // heroPos *= BOX2D_PIXELS_PER_METER;

  // int halfWidth = AREA_WIDTH / 2;
  // int halfHeight = AREA_HEIGHT / 2;
  // int xValue = heroPos.x / halfWidth;
  // int yValue = heroPos.y / halfHeight;
  // int heroQuarter = xValue + (yValue) * 2;
    
  // const int UPPER_LEFT_X = Arena::WALL_SIDE_SIZE + 50;
  // const int UPPER_LEFT_Y = Arena::WALL_TOP_SIZE;
  // const int UPPER_RIGHT_X = AREA_WIDTH - Arena::WALL_SIDE_SIZE - 50;
  // const int UPPER_RIGHT_Y = Arena::WALL_TOP_SIZE;
  // const int LOWER_LEFT_X = Arena::WALL_SIDE_SIZE + 50;
  // const int LOWER_LEFT_Y = AREA_HEIGHT - Arena::WALL_TOP_SIZE/2;
  // const int LOWER_RIGHT_X = AREA_WIDTH - Arena::WALL_SIDE_SIZE - 50;
  // const int LOWER_RIGHT_Y = AREA_HEIGHT - Arena::WALL_TOP_SIZE/2;

  // int rand = m_random.computeUniformInteger(0,3);
  // while(rand == heroQuarter) {
  //   rand = m_random.computeUniformInteger(0,3);
  // }

  // sf::Vector2f offset = { m_random.computeUniformFloat(0.0f, 50.0f), m_random.computeUniformFloat(0.0f, 50.0f) };

  // sf::Vector2f enemyPos;
  // switch (rand) {
  //   case 0: //upper left corner
  //     enemyPos = sf::Vector2f(UPPER_LEFT_X, UPPER_LEFT_Y) + offset;
  //     break;

  //   case 1: //upper right corner
  //     enemyPos = sf::Vector2f(UPPER_RIGHT_X, UPPER_RIGHT_Y) + offset;
  //     break;

  //   case 2: //lower left corner
  //     enemyPos = sf::Vector2f(LOWER_LEFT_X, LOWER_LEFT_Y) + offset;
  //     break;

  //   default: //lower right corner
  //     enemyPos = sf::Vector2f(LOWER_RIGHT_X, LOWER_RIGHT_Y) + offset;
  // }

  //m_enemies.push_back(new Enemy(m_b2_world, m_events, enemyPos, multiplier));
}
