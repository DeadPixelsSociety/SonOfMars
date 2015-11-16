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

#ifndef LOCAL_TARGET_H
#define LOCAL_TARGET_H

#include <game/Entity.h>

#include "Game.h"

class Target {
public:
  Target(Origin origin, bool isHitbox, game::Entity *entity);

  Origin getOrigin() const;
  bool isHitbox() const;
  game::Entity* getEntity() const;

private:
  Origin m_origin;
  bool m_isHitbox;
  game::Entity *m_entity;
};

#endif // LOCAL_TARGET_H
