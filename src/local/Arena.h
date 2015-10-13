#ifndef ARENA_H
#define ARENA_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/EventManager.h>



class Arena: public game::Entity {
public:
  Arena(b2World &b2_world, game::EventManager& events);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;
    
private:
  game::EventManager& m_events;
  float m_timeElapsed;

};

#endif //ARENA_H
