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

#include "Enemy.h"

#include <cmath>

#include "local/config.h"

#include "Game.h"
#include "Target.h"

Enemy::Enemy(b2World &b2_world, game::EventManager& events, sf::Vector2f position)
: m_body(nullptr)
, m_target({0.0f, 0.0f}) {
  // Register events trigger
  events.registerHandler<CharacterLocationEvent>(&Enemy::onCharacterLocationEvent, this);

  // Set the initial position
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(position.x / BOX2D_PIXELS_PER_METER, position.y / BOX2D_PIXELS_PER_METER);

  b2CircleShape b2_circle;
  b2_circle.m_radius = ENEMY_WIDTH / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;

  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_body->CreateFixture(&b2_fixture)->SetUserData(new Target(Origin::ENEMY, false, this));
}

Enemy::~Enemy() {
  m_body->GetWorld()->DestroyBody(m_body);
}

void Enemy::update(const float dt) {
  // Manage the move
  // Compute enemy's rotation
  b2Vec2 dir = m_target - m_body->GetPosition();
  float norm = std::hypot(dir.x, dir.y);
  m_body->SetTransform(m_body->GetPosition(),
    (( dir.y < 0 ) ? -1 : 1) * acos( dir.x/norm) );
  // Set enemy's speed (constant)
  if ( norm > 3.0f*ENEMY_WIDTH / BOX2D_PIXELS_PER_METER )
    m_body->SetLinearVelocity((3.0f/norm)*dir);
  else // Useless when other enemies push
    m_body->SetLinearVelocity( b2Vec2(0,0) );
}

void Enemy::render(sf::RenderWindow& window) {
  sf::CircleShape circle;
  b2Vec2 b2_pos = m_body->GetPosition();
  circle.setOrigin(ENEMY_WIDTH, ENEMY_WIDTH);
  circle.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  circle.setRadius(ENEMY_WIDTH);
  circle.setFillColor(sf::Color::Cyan);
  window.draw(circle);

  // Orientation of enemy
  float angle = m_body->GetAngle();
  sf::RectangleShape rect({ENEMY_WIDTH * 2.0f, 4.0f});
  rect.setOrigin(ENEMY_WIDTH, 2.0f);
  rect.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  rect.setFillColor(sf::Color::Red);
  rect.setRotation(angle * 180 / M_PI);
  window.draw(rect);
}

game::EventStatus Enemy::onCharacterLocationEvent(game::EventType type, game::Event *event) {
  auto locationEvent = static_cast<CharacterLocationEvent *>(event);

  m_target = locationEvent->pos;

  return game::EventStatus::KEEP;
}
