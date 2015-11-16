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

#include "Target.h"

Target::Target(Origin origin, bool isHitbox, game::Entity *entity) 
: m_origin(origin)
, m_isHitbox(isHitbox)
, m_entity(entity) {
  // Ctor
}

Origin Target::getOrigin() const {
  return m_origin;
}

bool Target::isHitbox() const {
  return m_isHitbox;
}

game::Entity* Target::getEntity() const {
  return m_entity;
}
