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

#ifndef LOCAL_GAME_H
#define LOCAL_GAME_H

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include <game/Entity.h>
#include <game/Event.h>

enum Origin {
  CHARACTER,
  ENEMY,
};

struct SpawnMobEvent : public game::Event {
  static const game::EventType type = "SpawnMobEvent"_type;
  sf::Vector2f pos;
  float multiplier;
};

struct CharacterLocationEvent : public game::Event {
  static const game::EventType type = "CharacterLocationEvent"_type;
  b2Vec2 pos;
};

struct CharacterStatsEvent : public game::Event {
  static const game::EventType type = "CharacterHealthEvent"_type;
  int characterHealth;
  int characterMaxHealth;
  int characterGold;
  int characterDamage;
  int characterArmor;
  int characterRegenValue;
  int characterRegenRate;
};

struct EnemyDeathEvent : public game::Event {
  static const game::EventType type = "EnemyDeathEvent"_type;
  int givenGold;
};

// Sound-specific events
struct CharacterHitEnemyEvent : public game::Event {
  static const game::EventType type = "CharacterHitEnemyEvent"_type;
  int numberOfHits;
  // bools or enums or ints to pass kinds of enemies (with metal armor…)
};

struct EnemyHitCharacterEvent : public game::Event {
  static const game::EventType type = "EnemyHitCharacterEvent"_type;
  int damages;
};

struct CharacterDeathEvent : public game::Event {
  static const game::EventType type = "CharacterDeathEvent"_type;
};

// EnemyDeathEvent already defined

struct CharacterMovementEvent : public game::Event {
  static const game::EventType type = "CharacterMovementEvent"_type;
  bool moves;
  // Maybe send speed to set pitch
};

#endif // LOCAL_GAME_H
