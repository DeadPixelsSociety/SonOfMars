#include "Character.h"

#include "local/config.h"

Character::Character(b2World &b2_world)
: m_body(nullptr) {
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(0.0f / BOX2D_PIXELS_PER_METER, 0.0f / BOX2D_PIXELS_PER_METER);
  b2CircleShape b2_circle;
  b2_circle.m_radius = 10.0f / BOX2D_PIXELS_PER_METER;
  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;
  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_body->CreateFixture(&b2_fixture);
}


void Character::update(const float dt) {

}

void Character::render(sf::RenderWindow& window) {
  sf::CircleShape circle;
  circle.setPosition(100,100);
  circle.setRadius(10);
  circle.setFillColor(sf::Color::White);
  window.draw(circle);
}
