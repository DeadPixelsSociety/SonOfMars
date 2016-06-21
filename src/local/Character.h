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

#ifndef CHARACTER_H
#define CHARACTER_H

#include <set>
#include <vector>

#include <Box2D/Box2D.h>

#include <game/Animation.h>
#include <game/Camera.h>
#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>

#include "Enemy.h"
#include "Merchant.h"
#include "Target.h"

class Character: public game::Entity {
public:
  enum Direction : unsigned int {
    UP      = 0x1,
    DOWN    = 0x2,
    LEFT    = 0x4,
    RIGHT   = 0x8,
    NONE    = 0x0,
  };

public:
  Character(b2World &b2_world, game::EventManager& events, game::ResourceManager &resources);

  Character(const Character&) = delete;
  Character& operator=(const Character&) = delete;

  Character(Character&&) = delete;
  Character& operator=(Character&&) = delete;

  virtual ~Character();

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  void death();

  game::EventStatus onEnemyDeathEvent(game::EventType type, game::Event *event);
  game::EventStatus onEndWaveEvent(game::EventType type, game::Event *event);

  // Events
  void move(Direction direction);
  void setTarget(sf::Vector2f mousePos);
  void simpleAttack();
  void buyDamage();
  void buyMaxHealth();
  void buyRegenValue();

  void setMaxHealth(float maxHealth);
  float getMaxHealth() const;
  void addToMaxHealth(float value);
  void substractToMaxHealth(float value);

  void setHealth(float health);
  float getHealth() const;
  void addToHealth(float value);
  void substractToHealth(float value);

  void setArmor(float armor);
  int getArmor() const;

  void setGold(int gold);
  int getGold() const;
  void addToGold(int value);
  void substractToGold(int value);

  void acquiredEnemy(Enemy* enemy);
  void lostEnemy(Enemy* enemy);

  static constexpr float CHARACTER_SPRITE_WIDTH = 760.0f;
  static constexpr float CHARACTER_SPRITE_HEIGHT = 954.0f;
  static constexpr float CHARACTER_SPRITE_RATIO = CHARACTER_SPRITE_WIDTH / CHARACTER_SPRITE_HEIGHT;

  static constexpr float CHARACTER_WIDTH = 100.0f;
  static constexpr float CHARACTER_HEIGHT = CHARACTER_WIDTH / CHARACTER_SPRITE_RATIO;

  static constexpr float CHARACTER_WIDTH_SCALE = CHARACTER_WIDTH / CHARACTER_SPRITE_WIDTH;
  static constexpr float CHARACTER_HEIGHT_SCALE = CHARACTER_HEIGHT / CHARACTER_SPRITE_HEIGHT;

private:
  b2Body *m_body;
  game::EventManager& m_events;
  sf::Texture *m_animLeftTexture;
  sf::Texture *m_animRightTexture;
  sf::Texture *m_animBottomTexture;
  sf::Texture *m_animTopTexture;

  sf::Texture *m_animLeftPauseTexture;
  sf::Texture *m_animRightPauseTexture;
  sf::Texture *m_animBottomPauseTexture;
  sf::Texture *m_animTopPauseTexture;

  game::Animation m_leftAnimation;
  game::Animation m_rightAnimation;
  game::Animation m_bottomAnimation;
  game::Animation m_topAnimation;

  game::Animation m_leftPauseAnimation;
  game::Animation m_rightPauseAnimation;
  game::Animation m_bottomPauseAnimation;
  game::Animation m_topPauseAnimation;

  game::Animation *m_currentAnimation;

  float m_timeElapsedAttack;

  Direction m_verticalDirection;
  Direction m_horizontalDirection;
  unsigned int m_spriteDirection;
  float m_timeElapsedAnimation;
  unsigned int m_animationCounter;

  b2Vec2 m_target;
  float m_maxHealth;
  float m_health;
  float m_damage;
  float m_armor;
  int m_gold;
  float m_regenerationValue; // The player regenerate m_regenerationValue per m_regenerationRate second
  float m_regenerationRate;
  float m_attackPeriod;

  std::set<Enemy *> m_visibleEnemies;
  Merchant *m_visibleMerchant;
  std::vector<Target *> m_targets;
};

#endif //CHARACTER_H
