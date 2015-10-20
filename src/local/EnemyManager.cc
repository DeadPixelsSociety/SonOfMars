#include "EnemyManager.h"

#include "Game.h"

EnemyManager::EnemyManager(game::EventManager& events, b2World &b2_world, Character &character)
: m_b2_world(b2_world)
, m_character(character) {
  // Register event
  events.registerHandler<SpawnMobEvent>(&EnemyManager::onSpawnMobEvent, this);
}

EnemyManager::~EnemyManager() {
  for (auto enemy : m_enemies) {
    delete enemy;
  }
}

void EnemyManager::update(const float dt) {
  for (auto enemy : m_enemies) {
    enemy->update(dt);
  }
}

void EnemyManager::render(sf::RenderWindow& window) {
  for (auto enemy : m_enemies) {
    enemy->render(window);
  }
}

game::EventStatus EnemyManager::onSpawnMobEvent(game::EventType type, game::Event *event) {
  auto spawnEvent = static_cast<SpawnMobEvent *>(event);

  m_enemies.push_back(new Enemy(m_b2_world, spawnEvent->pos, m_character));
  
  return game::EventStatus::KEEP;
}
