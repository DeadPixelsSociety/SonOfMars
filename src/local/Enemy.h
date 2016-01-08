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

#ifndef ENEMY_H
#define ENEMY_H

#include <Box2D/Box2D.h>
#include <set>
#include <iostream>

#include <game/Entity.h>
#include <game/EventManager.h>

#include "Target.h"

class Character;

class Enemy: public game::Entity {


public:
  Enemy(b2World &b2_world, game::EventManager& events, sf::Vector2f position,float multiplier);

  Enemy(const Enemy&) = delete;
  Enemy& operator=(const Enemy&) = delete;

  Enemy(Enemy&&) = delete;
  Enemy& operator=(Enemy&&) = delete;

  virtual ~Enemy();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  void death();

  // Events
  game::EventStatus onCharacterLocationEvent(game::EventType type, game::Event *event);
  void simpleAttack();

  void acquiredCharacter(Character* character);
  void lostCharacter(Character* character);

  static constexpr float ENEMY_WIDTH = 10.0f;

    void setHealth(float health);
    float getHealth() const;
    void addToHealth(float value);
    void substractToHealth(float value);

    void setArmor(float armor);
    float getArmor() const;

private:
  b2Body *m_body;
  b2Vec2 m_target;
  game::EventManager& m_events;
  std::vector<Target *> m_targets;
  float m_maxHealth;
  float m_health;
  float m_damage;
  float m_armor;
  int m_goldGiven;
  float m_speed;
  float m_attackPeriod;
  float m_timeElapsed;
  std::set<Character *> m_visibleCharacter;
};

#endif //ENEMY_H
