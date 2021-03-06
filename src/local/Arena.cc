/*
 * Son of Mars
 *
 * Copyright (c) 2015-2016, Team Son of Mars
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <cmath>

#include "Arena.h"

#include "Game.h"

Arena::Arena(b2World &b2_world, game::ResourceManager &resources)
: m_background(nullptr) {
  static constexpr float B2_WIDTH = AREA_WIDTH / BOX2D_PIXELS_PER_METER;
  static constexpr float B2_HEIGHT = AREA_HEIGHT / BOX2D_PIXELS_PER_METER;
  static constexpr float X_TOP = WALL_TOP_SIZE / BOX2D_PIXELS_PER_METER;
  static constexpr float X_SIDE = WALL_SIDE_SIZE / BOX2D_PIXELS_PER_METER;
  static constexpr float X = 32.0f / BOX2D_PIXELS_PER_METER;

  m_background = resources.getTexture("ground.jpg");
  assert(m_background != nullptr);

  static constexpr float B2_WALL_TOP_SIZE = X_TOP / 2.0f;
  static constexpr float B2_WALL_SIDE_SIZE = X_SIDE / 2.0f;
  static constexpr float B2_WALL_SIZE = X / 2.0f;

  // Wall left
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_staticBody;
  b2_bodyDef.position.Set(B2_WALL_SIDE_SIZE, B2_HEIGHT / 2.0f);

  b2Vec2 vertices[5];
  vertices[0].Set(-B2_WALL_SIDE_SIZE, -B2_HEIGHT / 2.0f);
  vertices[1].Set( B2_WALL_SIDE_SIZE, -B2_HEIGHT / 2.0f);
  vertices[2].Set( B2_WALL_SIDE_SIZE,  B2_HEIGHT / 2.0f);
  vertices[3].Set(-B2_WALL_SIDE_SIZE,  B2_HEIGHT / 2.0f);

  b2PolygonShape b2_boxShape;
  b2_boxShape.Set(vertices, 4);

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_boxShape;

  b2Body *b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Wall right
  b2_bodyDef.position.Set(B2_WIDTH - B2_WALL_SIDE_SIZE, B2_HEIGHT / 2.0f);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Wall top
  b2_bodyDef.position.Set(B2_WIDTH / 2.0f, B2_WALL_TOP_SIZE);

  vertices[0].Set(-B2_WIDTH / 2.0f, -B2_WALL_TOP_SIZE);
  vertices[1].Set( B2_WIDTH / 2.0f, -B2_WALL_TOP_SIZE);
  vertices[2].Set( B2_WIDTH / 2.0f,  B2_WALL_TOP_SIZE);
  vertices[3].Set(-B2_WIDTH / 2.0f,  B2_WALL_TOP_SIZE);

  b2_boxShape.Set(vertices, 4);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Wall right
  b2_bodyDef.position.Set(B2_WIDTH / 2.0f, B2_HEIGHT - B2_WALL_SIZE);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Défine corner top-left
  /*b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_staticBody;
  b2_bodyDef.position.Set(X_SIDE, X_TOP);

  b2Vec2 vertices[5];
  vertices[0].Set(-X_SIDE, -X_TOP);
  vertices[1].Set( X_SIDE, -X_TOP);
  vertices[2].Set( X_SIDE,  0);
  vertices[3].Set( 0,  X_TOP);
  vertices[4].Set(-X_SIDE,  X_TOP);

  b2PolygonShape b2_boxShape;
  b2_boxShape.Set(vertices, 5);

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_boxShape;

  b2Body *b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
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
  m_walls.push_back(b2_body);
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
  m_walls.push_back(b2_body);
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
  m_walls.push_back(b2_body);
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
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Wall right
  b2_bodyDef.position.Set(B2_WIDTH - B2_WALL_SIZE, B2_HEIGHT / 2.0f);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
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
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Wall right
  b2_bodyDef.position.Set(B2_WIDTH / 2.0f, B2_HEIGHT - B2_WALL_SIZE);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);*/
}

Arena::~Arena() {
  b2World *b2_world = m_walls[0]->GetWorld();
  for (auto wall : m_walls) {
    b2_world->DestroyBody(wall);
  }
}

void Arena::render(sf::RenderWindow& window) {
  sf::Sprite sprite;
  sprite.setTexture(*m_background);
  sprite.setScale(AREA_WIDTH / 3000.0f, AREA_HEIGHT / 1688.0f);
  window.draw(sprite);
}
