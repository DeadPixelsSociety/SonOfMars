#ifndef ARENA_H
#define ARENA_H

#include <Box2D/Box2D.h>
#include "Entity.h"

static constexpr float BOX2D_SCALE = 0.01f;

class Arena: public Entity {
public:
  Character(b2World &b2_world);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;
    
private:
  b2Body *m_body; 

};
#endif //ARENA_H
