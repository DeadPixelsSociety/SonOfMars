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

#include "Arena.h"

#include "local/config.h"

#include "Game.h"

static constexpr float WALL_SIZE = 32.0f;

static constexpr float SPAWN_PERIOD = 5.0f;

static constexpr int MAX_ENEMIES_PER_WAVE = 10;
static constexpr int INCREASE_ENEMY_POWER_RATE = 5; // every INCREASE_ENEMY_POWER_RATE, enemies will get more powerful

Arena::Arena(b2World &b2_world, game::EventManager& events)
: m_events(events)
, m_timeElapsed(SPAWN_PERIOD-2.0f)
, m_enemyCounter(0)
, m_waveNumber(1) {
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
  b2_body->CreateFixture(&b2_fixture);
}

Arena::~Arena() {
  b2World *b2_world = m_walls[0]->GetWorld();
  for (auto wall : m_walls) {
    b2_world->DestroyBody(wall);
  }
}

void Arena::update(const float dt)
{
  if (m_timeElapsed >= SPAWN_PERIOD)
  {
    game::Random random;
    if(m_enemyCounter<=0)
    {
        m_enemyCounter=random.computeUniformInteger(1,MAX_ENEMIES_PER_WAVE);
    }
    spawnEnemy(random);
    m_enemyCounter--;
    if(m_enemyCounter<=0)
    {
        m_timeElapsed -= SPAWN_PERIOD;
        m_waveNumber++;
    }
  }
  else
  {
    m_timeElapsed += dt;
  }
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

void Arena::spawnEnemy(game::Random random)
{
    // Make the new ennemy spawn randomly near one of the corners
    SpawnMobEvent event;
    event.multiplier=(m_waveNumber/INCREASE_ENEMY_POWER_RATE)+1;
    switch (random.computeUniformInteger(0,3))
    {
        case 0:
            event.pos = sf::Vector2f(42.0f, 42.0f);
            break;
        case 1:
            event.pos = sf::Vector2f(800.0f-42.0f, 42.0f);
            break;
        case 2:
            event.pos = sf::Vector2f(42.0f, 600.0f-42.0f);
            break;
        default:
            event.pos = sf::Vector2f(800.0f-42.0f, 600.0f-42.0f);
    }
    m_events.triggerEvent(&event);
}
