#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>

class Character: public game::Entity {
public:
  enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE,
  };

public:
  Character(b2World &b2_world);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  void move(Direction direction);

  static constexpr float CHARACTER_WIDTH = 10.0f;
    
private:
  b2Body *m_body; 
  Direction m_verticalDirection;
  Direction m_horizontalDirection;
};

#endif //CHARACTER_H
