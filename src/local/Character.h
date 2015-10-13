#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>

#include <game/Entity.h>

#include <cmath>

#define _USE_MATH_DEFINES

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


  b2Vec2 getPosition();


  // Events
  void move(Direction direction);
  void setTarget(sf::Vector2f mousePos);

  static constexpr float CHARACTER_WIDTH = 10.0f;
    
private:
  b2Body *m_body;
  Direction m_verticalDirection;
  Direction m_horizontalDirection;

  b2Vec2 m_target;
};

#endif //CHARACTER_H
