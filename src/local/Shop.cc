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

#include "local/config.h"

#include "Shop.h"

Shop::Shop(b2World &b2_world/*, game::ResourceManager &resources*/)
: m_background(nullptr) {
  static constexpr float B2_WALL_SIDE_SIZE = (SHOP_WIDTH / 40.0f) / BOX2D_PIXELS_PER_METER;
  static constexpr float B2_WALL_TOP_SIZE = (SHOP_HEIGHT / 40.0f) / BOX2D_PIXELS_PER_METER;
  static constexpr float B2_WIDTH = SHOP_WIDTH / BOX2D_PIXELS_PER_METER;
  static constexpr float B2_HEIGHT = SHOP_HEIGHT / BOX2D_PIXELS_PER_METER;
  static constexpr float B2_OFFSET_X = AREA_WIDTH / BOX2D_PIXELS_PER_METER;

  // Wall left
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_staticBody;
  b2_bodyDef.position.Set(B2_OFFSET_X + B2_WALL_SIDE_SIZE, B2_HEIGHT / 2.0f);

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
  b2_bodyDef.position.Set(B2_OFFSET_X + B2_WIDTH - B2_WALL_SIDE_SIZE, B2_HEIGHT / 2.0f);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // // Wall top
  b2_bodyDef.position.Set(B2_OFFSET_X + B2_WIDTH / 2.0f, B2_WALL_TOP_SIZE);

  vertices[0].Set(-B2_WIDTH / 2.0f, -B2_WALL_TOP_SIZE);
  vertices[1].Set( B2_WIDTH / 2.0f, -B2_WALL_TOP_SIZE);
  vertices[2].Set( B2_WIDTH / 2.0f,  B2_WALL_TOP_SIZE);
  vertices[3].Set(-B2_WIDTH / 2.0f,  B2_WALL_TOP_SIZE);

  b2_boxShape.Set(vertices, 4);

  b2_fixture.shape = &b2_boxShape;

  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);

  // Wall bottom
  b2_bodyDef.position.Set(B2_OFFSET_X + B2_WIDTH / 2.0f, B2_HEIGHT - B2_WALL_TOP_SIZE);
  b2_body = b2_world.CreateBody(&b2_bodyDef);
  m_walls.push_back(b2_body);
  b2_body->CreateFixture(&b2_fixture);
}


void Shop::render(sf::RenderWindow& window) {
  sf::RectangleShape rect(sf::Vector2f(SHOP_WIDTH, SHOP_HEIGHT));
  //rect.setColor(sf::Color(0, 255, 0));
  rect.setFillColor(sf::Color::Green);

  rect.setPosition({SHOP_OFFSET_X, 0.0f});
  window.draw(rect);
  /*sf::Sprite sprite;
  sprite.setTexture(*m_background);
  sprite.setScale(AREA_WIDTH / 3000.0f, AREA_HEIGHT / 1688.0f);
  window.draw(sprite);*/
}
