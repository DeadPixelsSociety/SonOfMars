#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>

class EnemyManager: public game::Entity {
public:
  EnemyManager(game::EventManager& events);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onSpawnMobEvent(game::EventType type, game::Event *event);

private:

};

#endif // ENEMY_MANAGER_H
