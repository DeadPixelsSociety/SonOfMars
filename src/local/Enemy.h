#ifndef ENEMY_H
#define ENEMY_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>

#include <cmath>
#define _USE_MATH_DEFINES

#include "Character.h"

class Enemy: public game::Entity {


public:
  Enemy(b2World &b2_world, b2Vec2 position, Character &hero);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;


  static constexpr float CHARACTER_WIDTH = 10.0f;
    
private:
  b2Body *m_body;

  b2Vec2 m_target;
  Character &m_hero;
};

#endif //ENEMY_H
