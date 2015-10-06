#include "Arena.h"

#include "local/config.h"

static constexpr float WALL_SIZE = 32.0f;

Arena::Arena(b2World &b2_world) {
  static constexpr float B2_WIDTH = AREA_WIDTH / BOX2D_PIXELS_PER_METER;
  static constexpr float B2_HEIGHT = AREA_HEIGHT / BOX2D_PIXELS_PER_METER;
  static constexpr float X = WALL_SIZE / BOX2D_PIXELS_PER_METER;

  // Défine corner top-left
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_staticBody;
  b2_bodyDef.position.Set(X, X);

  b2Vec2 vertices[5];
  vertices[0].Set(-X, -X);
  vertices[1].Set( X, -X);
  vertices[2].Set( X,  0);
  vertices[3].Set( 0,  X);
  vertices[4].Set(-X,  X);

  b2PolygonShape b2_boxShape;
  b2_boxShape.Set(vertices, 5);

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_boxShape;

  b2Body *b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  // Défine corner top-right
  b2_bodyDef.position.Set(B2_WIDTH - X, X);

  vertices[0].Set(-X, -X);
  vertices[1].Set( X, -X);
  vertices[2].Set( X,  X);
  vertices[3].Set( 0,  X);
  vertices[4].Set(-X,  0);

  b2_boxShape.Set(vertices, 5);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  // Défine corner bottom-right
  b2_bodyDef.position.Set(B2_WIDTH - X, B2_HEIGHT - X);

  vertices[0].Set( 0, -X);
  vertices[1].Set( X, -X);
  vertices[2].Set( X,  X);
  vertices[3].Set(-X,  X);
  vertices[4].Set(-X,  0);

  b2_boxShape.Set(vertices, 5);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  // Défine corner bottom-right
  b2_bodyDef.position.Set(X, B2_HEIGHT - X);

  vertices[0].Set(-X, -X);
  vertices[1].Set( 0, -X);
  vertices[2].Set( X,  0);
  vertices[3].Set( X,  X);
  vertices[4].Set(-X,  X);

  b2_boxShape.Set(vertices, 5);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  static constexpr float B2_WALL_SIZE = X / 2.0f;

  // Wall left
  b2_bodyDef.position.Set(B2_WALL_SIZE, B2_HEIGHT / 2.0f);

  vertices[0].Set(-B2_WALL_SIZE, -(B2_HEIGHT - (X * 4.0f)) / 2.0f);
  vertices[1].Set( B2_WALL_SIZE, -(B2_HEIGHT - (X * 4.0f)) / 2.0f);
  vertices[2].Set( B2_WALL_SIZE,  (B2_HEIGHT - (X * 4.0f)) / 2.0f);
  vertices[3].Set(-B2_WALL_SIZE,  (B2_HEIGHT - (X * 4.0f)) / 2.0f);

  b2_boxShape.Set(vertices, 4);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  // Wall right
  b2_bodyDef.position.Set(B2_WIDTH - B2_WALL_SIZE, B2_HEIGHT / 2.0f);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  // Wall top
  b2_bodyDef.position.Set(B2_WIDTH / 2.0f, B2_WALL_SIZE);

  vertices[0].Set(-(B2_WIDTH - (X * 4.0f)) / 2.0f, -B2_WALL_SIZE);
  vertices[1].Set( (B2_WIDTH - (X * 4.0f)) / 2.0f, -B2_WALL_SIZE);
  vertices[2].Set( (B2_WIDTH - (X * 4.0f)) / 2.0f,  B2_WALL_SIZE);
  vertices[3].Set(-(B2_WIDTH - (X * 4.0f)) / 2.0f,  B2_WALL_SIZE);

  b2_boxShape.Set(vertices, 4);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);

  // Wall right
  b2_bodyDef.position.Set(B2_WIDTH / 2.0f, B2_HEIGHT - B2_WALL_SIZE);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  b2_body->CreateFixture(&b2_fixture);
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
