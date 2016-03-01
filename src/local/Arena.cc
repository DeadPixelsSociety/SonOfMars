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

#include "Arena.h"

#include "local/config.h"

#include "Game.h"

static constexpr float WALL_TOP_SIZE = 192.0f * (AREA_WIDTH/3000.0f);
static constexpr float WALL_SIDE_SIZE = 16.0f;

static constexpr float SPAWN_PERIOD = 10.0f;

static constexpr int MIN_ENEMIES_PER_WAVE = 3;
static constexpr int INCREASE_ENEMY_POWER_RATE = 5; // every INCREASE_ENEMY_POWER_RATE, enemies will get more powerful

Arena::Arena(b2World &b2_world, game::EventManager& events, game::ResourceManager &resources)
: m_events(events)
, m_timeElapsed(SPAWN_PERIOD-2.0f)
, m_enemyCounter(0)
, m_waveNumber(1)
, m_background(nullptr) {
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

void Arena::update(const float dt)
{
  if (m_timeElapsed >= SPAWN_PERIOD)
  {
    game::Random random;
    if(m_enemyCounter<=0)
    {
        m_enemyCounter=random.computeUniformInteger(MIN_ENEMIES_PER_WAVE + m_waveNumber, MIN_ENEMIES_PER_WAVE * (m_waveNumber + 1));
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
  sf::Sprite sprite;
  sprite.setTexture(*m_background);
  sprite.setScale(AREA_WIDTH / 3000.0f, AREA_HEIGHT / 1688.0f);
  window.draw(sprite);
}

void Arena::spawnEnemy(game::Random &random)
{
    // Make the new ennemy spawn randomly near one of the corners
    SpawnMobEvent event;
    event.multiplier=(m_waveNumber/INCREASE_ENEMY_POWER_RATE)+1;
    
    //m_view = window.getDefaultView();
    
    const int UPPER_LEFT_X = WALL_SIDE_SIZE + 50;
    const int UPPER_LEFT_Y = WALL_TOP_SIZE;
    const int UPPER_RIGHT_X = AREA_WIDTH - WALL_SIDE_SIZE - 50;
    const int UPPER_RIGHT_Y = WALL_TOP_SIZE;
    const int LOWER_LEFT_X = WALL_SIDE_SIZE + 50;
    const int LOWER_LEFT_Y = AREA_HEIGHT - WALL_TOP_SIZE/2;
    const int LOWER_RIGHT_X = AREA_WIDTH - WALL_SIDE_SIZE - 50;
    const int LOWER_RIGHT_Y = AREA_HEIGHT - WALL_TOP_SIZE/2;
    switch (random.computeUniformInteger(0,3))
    {
        case 0: //upper left corner
            event.pos = sf::Vector2f(UPPER_LEFT_X, UPPER_LEFT_Y);
            break;
        case 1: //upper right corner
            event.pos = sf::Vector2f(UPPER_RIGHT_X, UPPER_RIGHT_Y);
            break;
        case 2: //lower left corner
            event.pos = sf::Vector2f(LOWER_LEFT_X, LOWER_LEFT_Y);
            break;
        default: //lower right corner
            event.pos = sf::Vector2f(LOWER_RIGHT_X, LOWER_RIGHT_Y);
    }
    m_events.triggerEvent(&event);
}
