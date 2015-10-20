#include "EnemyManager.h"

#include "Game.h"

EnemyManager::EnemyManager(b2World &b2_world, game::EventManager& events)
: m_b2_world(b2_world)
, m_events(events) {
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

  m_enemies.push_back(new Enemy(m_b2_world, m_events, spawnEvent->pos));
  
  return game::EventStatus::KEEP;
}
