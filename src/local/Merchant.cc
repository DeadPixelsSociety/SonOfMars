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

#include "Merchant.h"

#include "local/config.h"

Merchant::Merchant(b2World &b2_world, Skill skill, sf::Vector2f position)
: m_skill(skill)
, m_body(nullptr) {
  // Set the initial position
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_staticBody;
  b2_bodyDef.position.Set(position.x / BOX2D_PIXELS_PER_METER, position.y / BOX2D_PIXELS_PER_METER);

  b2CircleShape b2_circle;
  b2_circle.m_radius = MERCHANT_WIDTH / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;

  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_target = std::make_shared<Target>(Target(Origin::MERCHANT, false, this));
  m_body->CreateFixture(&b2_fixture)->SetUserData(m_target.get());
}

Skill Merchant::getSkill() {
  return m_skill;
}
