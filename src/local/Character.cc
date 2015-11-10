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

#include "Character.h"

#include <cmath>

#include "local/config.h"

#include "Game.h"

static constexpr float VELOCITY_STEP = 5.0f;

Character::Character(b2World &b2_world, game::EventManager& events)
: m_body(nullptr)
, m_events(events)
, m_verticalDirection(NONE)
, m_horizontalDirection(NONE)
, m_health(100) {
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(AREA_WIDTH / 2.0f / BOX2D_PIXELS_PER_METER, AREA_HEIGHT / 2.0f / BOX2D_PIXELS_PER_METER);

  b2CircleShape b2_circle;
  b2_circle.m_radius = CHARACTER_WIDTH / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;

  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_body->CreateFixture(&b2_fixture);
}

Character::~Character() {
  m_body->GetWorld()->DestroyBody(m_body);
}

void Character::update(const float dt) {
  // Manage the move
  b2Vec2 b2_velocity = m_body->GetLinearVelocity();
  if (m_verticalDirection == Direction::UP) {
		if (m_horizontalDirection == Direction::RIGHT) {
			b2_velocity.y = -VELOCITY_STEP * sin(M_PI/4);
			b2_velocity.x = +VELOCITY_STEP * cos(M_PI/4);
		}else if (m_horizontalDirection == Direction::LEFT) {
			b2_velocity.y = -VELOCITY_STEP * sin(M_PI/4);
			b2_velocity.x = -VELOCITY_STEP * cos(M_PI/4);
		}else{
    		b2_velocity.y = -VELOCITY_STEP;
			b2_velocity.x = 0.0f;
		}
  }else if (m_verticalDirection == Direction::DOWN) {
		if (m_horizontalDirection == Direction::RIGHT) {
			b2_velocity.y = +VELOCITY_STEP * sin(M_PI/4);
			b2_velocity.x = +VELOCITY_STEP * cos(M_PI/4);
		}else if (m_horizontalDirection == Direction::LEFT) {
			b2_velocity.y = +VELOCITY_STEP * sin(M_PI/4);
			b2_velocity.x = -VELOCITY_STEP * cos(M_PI/4);
		}else{
			b2_velocity.y = +VELOCITY_STEP;
			b2_velocity.x = 0.0f;
		}
	}else {
		if (m_horizontalDirection == Direction::RIGHT) {
			b2_velocity.y = 0.0f;
    		b2_velocity.x = +VELOCITY_STEP;
  		}else if (m_horizontalDirection == Direction::LEFT) {
			b2_velocity.y = 0.0f;
    		b2_velocity.x = -VELOCITY_STEP;
  		}else{
    		b2_velocity.y = 0.0f;
			b2_velocity.x = 0.0f;
  		}
	}

  // Apply the move
  m_body->SetLinearVelocity(b2_velocity);

  // Reset move
  m_verticalDirection = Direction::NONE;
  m_horizontalDirection = Direction::NONE;

  // Trigger location event
  CharacterLocationEvent event;
  event.pos = {m_body->GetPosition().x, m_body->GetPosition().y};
  m_events.triggerEvent(&event);

  // Trigger health event
  CharacterHealthEvent healthEvent;
  healthEvent.CharacterHealth=m_health;
  m_events.triggerEvent(&healthEvent);

}

void Character::render(sf::RenderWindow& window) {
  // Display the character
  sf::CircleShape circle;
  b2Vec2 b2_pos = m_body->GetPosition();
  circle.setOrigin(CHARACTER_WIDTH, CHARACTER_WIDTH);
  circle.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  circle.setRadius(CHARACTER_WIDTH);
  circle.setFillColor(sf::Color::Black);
  window.draw(circle);

  // Orientation of character
  float angle = m_body->GetAngle();
  sf::RectangleShape rect({CHARACTER_WIDTH * 2.0f, 4.0f});
  rect.setOrigin(CHARACTER_WIDTH, 2.0f);
  rect.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  rect.setFillColor(sf::Color::Red);
  rect.setRotation(angle * 180 / M_PI);
  window.draw(rect);
}

void Character::move(Direction direction) {
  switch (direction) {
  case UP:
  case DOWN:
    if (direction == UP) {
      m_verticalDirection = UP;
    }
    else {
      m_verticalDirection = DOWN;
    }
    break;
  case LEFT:
  case RIGHT:
    if (direction == LEFT) {
      m_horizontalDirection = LEFT;
    }
    else {
      m_horizontalDirection = RIGHT;
    }
    break;
  case NONE:
    break;
  }
}

void Character::setTarget(sf::Vector2f mousePos) {
  b2Vec2 b2_pos(m_body->GetPosition()), b2_newCharacterTarget;
  sf::Vector2i center(b2_pos.x*BOX2D_PIXELS_PER_METER,
                      b2_pos.y*BOX2D_PIXELS_PER_METER);
  float newAngle(0)
    , dist( std::hypot( mousePos.x - center.x, mousePos.y - center.y) );

  newAngle = (( mousePos.y < center.y ) ? -1 : 1)
    * acos((mousePos.x-center.x)/dist);

  m_body->SetTransform(b2_pos, newAngle);

  // Store cursor's position for Box2D and drawing usage
  m_target.x = mousePos.x / (double)BOX2D_PIXELS_PER_METER;
  m_target.y = mousePos.y / (double)BOX2D_PIXELS_PER_METER;
}

void Character::setHealth(int health)
{
    m_health=health;
}
int Character::getHealth()
{
    return m_health;
}
