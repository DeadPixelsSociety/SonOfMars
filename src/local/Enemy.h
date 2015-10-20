#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>

class Enemy: public game::Entity {


public:
  Enemy(b2World &b2_world, game::EventManager& events, sf::Vector2f position);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onCharacterLocationEvent(game::EventType type, game::Event *event);

  static constexpr float ENEMY_WIDTH = 10.0f;
    
private:
  b2Body *m_body;
  sf::Vector2f m_target;
};

#endif //ENEMY_H
