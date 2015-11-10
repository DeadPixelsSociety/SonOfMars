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
#include <iostream>

#include "local/config.h"

#include "Game.h"
#include "Target.h"

static constexpr float VELOCITY_STEP = 5.0f;

Character::Character(b2World &b2_world, game::EventManager& events)
: m_body(nullptr)
, m_events(events)
, m_verticalDirection(NONE)
, m_horizontalDirection(NONE)
, m_b2_hitbox(nullptr) {
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(AREA_WIDTH / 2.0f / BOX2D_PIXELS_PER_METER, AREA_HEIGHT / 2.0f / BOX2D_PIXELS_PER_METER);

  // Body 
  b2CircleShape b2_circle;
  b2_circle.m_radius = CHARACTER_WIDTH / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;

  m_body = b2_world.CreateBody(&b2_bodyDef);

  // Create the body fixture
  b2Fixture *fixture = m_body->CreateFixture(&b2_fixture);
  fixture->SetUserData(new Target(this, Origin::CHARACTER, false));

  // Create the hitbox fixture
  b2PolygonShape b2_hitbox;
  float hitboxSize = CHARACTER_WIDTH / BOX2D_PIXELS_PER_METER;
  b2_hitbox.SetAsBox(hitboxSize, hitboxSize, {hitboxSize, 0.0f}, 0.0f);
  b2_fixture.shape = &b2_hitbox;
  b2_fixture.isSensor = true;
  m_b2_hitbox = m_body->CreateFixture(&b2_fixture);
  m_b2_hitbox->SetUserData(new Target(this, Origin::CHARACTER, true));
}

Character::~Character() {
  delete static_cast<Target*>(m_b2_hitbox->GetUserData());
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
}

void Character::render(sf::RenderWindow& window) {
  // Trigger location event
  CharacterLocationEvent event;
  event.pos = {m_body->GetPosition().x * BOX2D_PIXELS_PER_METER, m_body->GetPosition().y * BOX2D_PIXELS_PER_METER};
  m_events.triggerEvent(&event);

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
  sf::Vector2i center(b2_pos.x*BOX2D_PIXELS_PER_METER, b2_pos.y*BOX2D_PIXELS_PER_METER);
  float newAngle(0)
    , dist( sqrt(pow(mousePos.x - center.x, 2)+pow(mousePos.y - center.y, 2)) );

  // Ugliest way: (mousePos.y > center.y)*2-1
  newAngle = (( mousePos.y < center.y ) ? -1 : 1) * acos((mousePos.x-center.x)/dist);
  // TODO: explain why it is -1 : 1 and not 1 : -1
  
  m_body->SetTransform(b2_pos, newAngle);

  // Store cursor's position for Box2D usage
  m_target.x = mousePos.x / (double)BOX2D_PIXELS_PER_METER;
  m_target.y = mousePos.y / (double)BOX2D_PIXELS_PER_METER;
}

void Character::simpleAttack() {
  std::cout << "Attack" << std::endl;
}

void Character::addTarget(Entity *entity) {
  m_targets.push_back(entity);
}

void Character::removeTarget(Entity *entity) {
  m_targets.erase(std::remove(m_targets.begin(), m_targets.end(), entity));
}
