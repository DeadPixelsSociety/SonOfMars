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

#include "ContactListener.h"

#include <cassert>
#include <iostream>

#include "Character.h"

void ContactListener::BeginContact(b2Contact* b2_contact) {
  Contact contact = defineHitboxAndBody(b2_contact);
  // If useless case
  if (contact.hitbox == nullptr || contact.body == nullptr) {
    return;
  }

  // If the enemy hits the player
  if (contact.hitbox->getOrigin() == Origin::ENEMY) {
    std::cerr << "No yet implemented" << std::endl;
    assert(false);
    return;
  }

  // If the player hits the enemy
  if (contact.hitbox->getOrigin() == Origin::CHARACTER) {
    Character *character = static_cast<Character*>(contact.hitbox->getEntity());
    character->addTarget(contact.body->getEntity());
    return;
  }

  assert(false);
}

void ContactListener::EndContact(b2Contact* b2_contact) {
  Contact contact = defineHitboxAndBody(b2_contact);
  // If useless case
  if (contact.hitbox == nullptr || contact.body == nullptr) {
    return;
  }

  // If the enemy hits the player
  if (contact.hitbox->getOrigin() == Origin::ENEMY) {
    std::cerr << "No yet implemented" << std::endl;
    assert(false);
    return;
  }

  // If the player hits the enemy
  if (contact.hitbox->getOrigin() == Origin::CHARACTER) {
    Character *character = static_cast<Character*>(contact.hitbox->getEntity());
    character->removeTarget(contact.body->getEntity());
    return;
  }

  assert(false);
}

ContactListener::Contact ContactListener::defineHitboxAndBody(b2Contact *b2_contact) {
  Target *targetA = static_cast<Target*>(b2_contact->GetFixtureA()->GetUserData());
  Target *targetB = static_cast<Target*>(b2_contact->GetFixtureB()->GetUserData());
  Contact contact;
  contact.hitbox = nullptr;
  contact.body = nullptr;

  // Check if is a collision with a wall
  if (targetA == nullptr || targetB == nullptr) {
    return contact;
  }

  // Check if a collision between two enemies
  if (targetA->getOrigin() == Origin::ENEMY && targetB->getOrigin() == Origin::ENEMY) {
    return contact;
  }

  // Check if a collision between two hitbox or two body
  if (targetA->isHitbox() == targetB->isHitbox()) {
    return contact;
  }

  // Define who is hitbox
  if (targetA->isHitbox()) {
    contact.hitbox = targetA;
    contact.body = targetB;
  }
  else {
    contact.hitbox = targetB;
    contact.body = targetA;
  }

  return contact;
}
