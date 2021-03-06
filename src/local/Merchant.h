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

#ifndef _MERCHANT_H
#define _MERCHANT_H

#include <memory>

#include <Box2D/Box2D.h>

#include <game/Entity.h>

#include "Target.h"

enum Skill {
  LIFE,
};

class Merchant: public game::Entity {
public:
  Merchant(b2World &b2_world, Skill skill, sf::Vector2f position);

  // virtual void update(float dt) override;
  // virtual void render(sf::RenderWindow& window) override;

  Skill getSkill();

  static constexpr float MERCHANT_WIDTH = 10.0f;

private:
  Skill m_skill;
  b2Body *m_body;
  std::shared_ptr<Target> m_target;
};

#endif // _MERCHANT_H
