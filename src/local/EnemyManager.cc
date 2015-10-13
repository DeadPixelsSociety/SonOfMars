#include "EnemyManager.h"

#include "Game.h"

EnemyManager::EnemyManager(game::EventManager& events) {
  // Register event
  events.registerHandler<SpawnMobEvent>(&EnemyManager::onSpawnMobEvent, this);
}

void EnemyManager::update(const float dt) {

}

void EnemyManager::render(sf::RenderWindow& window) {

}

game::EventStatus EnemyManager::onSpawnMobEvent(game::EventType type, game::Event *event) {
  auto spawnEvent = static_cast<SpawnMobEvent *>(event);
  
  return game::EventStatus::KEEP;
}
