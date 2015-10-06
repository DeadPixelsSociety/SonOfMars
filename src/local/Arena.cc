#include "Arena.h"

#include "local/config.h"

static constexpr float WALL_SIZE = 32.0f;

Arena::Arena(b2World &b2_world)
: m_body(nullptr) {
  /*b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(100.0f * BOX2D_SCALE, 100.0f * BOX2D_SCALE);
  b2CircleShape b2_circle;
  b2_circle.m_radius = 100.0f * BOX2D_SCALE;
  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;
  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_body->CreateFixture(&b2_fixture);*/
  /*b2Vec2 vertices[8];

  vertices[0].Set(- half_w, X * half_h);
  vertices[1].Set(- X * half_w, half_h);
  vertices[2].Set(  X * half_w, half_h);
  vertices[3].Set(  half_w, X * half_h);
  vertices[4].Set(  half_w, - X * half_h);
  vertices[5].Set(  X * half_w, - half_h);
  vertices[6].Set(- X * half_w, - half_h);
  vertices[7].Set(- half_w, - X * half_h);*/

  /*b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(0.0f / BOX2D_PIXELS_PER_METER, 0.0f / BOX2D_PIXELS_PER_METER);

  b2CircleShape b2_circle;
  b2_circle.m_radius = 10.0f / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;
  
  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_body->CreateFixture(&b2_fixture);*/
}

void Arena::update(const float dt) {

}

void Arena::render(sf::RenderWindow& window) {
  sf::RectangleShape wall;
  // Top wall
  wall.setSize({AREA_WIDTH, WALL_SIZE});
  wall.setFillColor(sf::Color::Blue);
  window.draw(wall);

  // Bottom wall
  //wall.setSize({AREA_WIDTH, WALL_SIZE});
  wall.setOrigin(0.0f, WALL_SIZE);
  wall.setPosition(0.0f, AREA_HEIGHT);
  window.draw(wall);

  // Left wall
  wall.setOrigin(0.0f, 0.0f);
  wall.setSize({WALL_SIZE, AREA_HEIGHT});
  wall.setPosition(0.0f, 0.0f);
  window.draw(wall);

  // Right wall
  wall.setOrigin(WALL_SIZE, 0.0f);
  wall.setPosition(AREA_WIDTH, 0.0f);
  window.draw(wall);
}
