#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>

#include "Character.h"
#include "Enemy.h"

class EnemyManager: public game::Entity {
public:
  EnemyManager(b2World &b2_world, game::EventManager& events);

  EnemyManager(const EnemyManager&) = delete;
  EnemyManager& operator=(const EnemyManager&) = delete;

  EnemyManager(EnemyManager&&) = delete;
  EnemyManager& operator=(EnemyManager&&) = delete;

  virtual ~EnemyManager();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onSpawnMobEvent(game::EventType type, game::Event *event);

private:
  std::vector<Enemy*> m_enemies;
  b2World &m_b2_world;
  game::EventManager& m_events;
};

#endif // ENEMY_MANAGER_H
