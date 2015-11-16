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

#ifndef LOCAL_CONTACT_LISTNER_H
#define LOCAL_CONTACT_LISTNER_H

#include <Box2D/Box2D.h>

#include <game/EventManager.h>

#include "Target.h"

class ContactListener : public b2ContactListener {
public:
  void BeginContact(b2Contact* contact) override;
  void EndContact(b2Contact* contact) override;

private:
  struct Contact {
    Target *hitbox;
    Target *body;
  };

private:
  Contact defineHitboxAndBody(b2Contact *contact);
};

#endif // LOCAL_CONTACT_LISTNER_H
