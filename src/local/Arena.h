#ifndef ARENA_H
#define ARENA_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>



class Arena: public game::Entity {
public:
  Arena(b2World &b2_world);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;
    
private:

};

#endif //ARENA_H
