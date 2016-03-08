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
#include <stdlib.h>

#include "local/config.h"

#include "Game.h"
#include "Target.h"

static constexpr float VELOCITY_STEP = 5.0f;
static constexpr float DEGTORAD = M_PI / 180.0f;
static constexpr float BASIC_MAX_HEALTH = 100.0f;
static constexpr float BASIC_DAMAGE = 3.0f;
static constexpr float BASIC_ARMOR = 0.0f;
static constexpr float BASE_REGEN_VALUE = 1.0f;
static constexpr float BASE_REGEN_RATE = 10.0f;
static constexpr float BASE_ATTACK_PERIOD = 0.25f;

static constexpr int SPRITE_WIDTH = 760;
static constexpr int SPRITE_HEIGHT = 940;
static constexpr int SPRITE_PAUSE_WIDTH = 788;
static constexpr int SPRITE_PAUSE_HEIGHT = 936;

static constexpr float FRAME_DURATION = 0.1f;
static constexpr int NUMBER_ANIMATIONS_BY_LINE = 4;
static constexpr int NUMBER_OF_LINES = 2;
static constexpr int NUMBER_OF_PAUSE_SPRITES = 16;
static constexpr int PAUSE_SPRITES_PER_LINE = 4;

Character::Character(b2World &b2_world, game::EventManager& events, game::ResourceManager &resources)
: game::Entity(5)
, m_body(nullptr)
, m_events(events)
, m_animLeftTexture(nullptr)
, m_animRightTexture(nullptr)
, m_animBottomTexture(nullptr)
, m_animTopTexture(nullptr)
, m_animLeftPauseTexture(nullptr)
, m_animRightPauseTexture(nullptr)
, m_animBottomPauseTexture(nullptr)
, m_animTopPauseTexture(nullptr)
, m_leftAnimation("Left")
, m_rightAnimation("Right")
, m_bottomAnimation("Bottom")
, m_topAnimation("Top")
, m_leftPauseAnimation("Pause Left")
, m_rightPauseAnimation("Pause Right")
, m_bottomPauseAnimation("PauseBottom")
, m_topPauseAnimation("Pause Top")
, m_currentAnimation(&m_bottomAnimation)
, m_timeElapsedAttack(0.0f)
, m_verticalDirection(NONE)
, m_horizontalDirection(NONE)
, m_spriteDirection(0)
, m_timeElapsedAnimation(0.0f)
, m_animationCounter(0)
, m_maxHealth(BASIC_MAX_HEALTH)
, m_health(m_maxHealth)
, m_damage(BASIC_DAMAGE)
, m_armor(BASIC_ARMOR)
, m_gold(0)
, m_regenerationValue(BASE_REGEN_VALUE) // The player regenerate m_regenerationValue over m_regenerationRate second
, m_regenerationRate(BASE_REGEN_RATE)
, m_attackPeriod(BASE_ATTACK_PERIOD)
{
  // Load textures
  m_animLeftTexture = resources.getTexture("character/character_left.png");
  assert(m_animLeftTexture != nullptr);

  m_animRightTexture = resources.getTexture("character/character_right.png");
  assert(m_animRightTexture != nullptr);

  m_animBottomTexture = resources.getTexture("character/character_bottom.png");
  assert(m_animBottomTexture != nullptr);

  m_animTopTexture = resources.getTexture("character/character_top.png");
  assert(m_animTopTexture != nullptr);

  m_animLeftPauseTexture = resources.getTexture("character/character_pause_left.png");
  assert(m_animLeftPauseTexture != nullptr);

  m_animRightPauseTexture = resources.getTexture("character/character_pause_right.png");
  assert(m_animRightPauseTexture != nullptr);

  m_animBottomPauseTexture = resources.getTexture("character/character_pause_bottom.png");
  assert(m_animBottomPauseTexture != nullptr);

  m_animTopPauseTexture = resources.getTexture("character/character_pause_top.png");
  assert(m_animTopPauseTexture != nullptr);

  // Create animation
  for(int counterLine=0;counterLine<NUMBER_OF_LINES;counterLine++) {
    for(int counterAnim=0;counterAnim<NUMBER_ANIMATIONS_BY_LINE;counterAnim++) {
      m_leftAnimation.addFrame(m_animLeftTexture, { counterAnim * SPRITE_WIDTH , counterLine * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT }, FRAME_DURATION);
      m_rightAnimation.addFrame(m_animRightTexture, { counterAnim * SPRITE_WIDTH, counterLine * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT }, FRAME_DURATION);
      m_bottomAnimation.addFrame(m_animBottomTexture, { counterAnim * SPRITE_WIDTH, counterLine * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT }, FRAME_DURATION);
      m_topAnimation.addFrame(m_animTopTexture, { counterAnim * SPRITE_WIDTH, counterLine * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT }, FRAME_DURATION);
    }
  }
  for(int sprite=0 ; sprite<NUMBER_OF_PAUSE_SPRITES ; sprite++) {
    m_leftPauseAnimation.addFrame(m_animLeftPauseTexture, { (sprite%PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_WIDTH, (sprite/PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_HEIGHT, SPRITE_PAUSE_WIDTH, SPRITE_PAUSE_HEIGHT }, FRAME_DURATION);
    m_rightPauseAnimation.addFrame(m_animRightPauseTexture, { (sprite%PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_WIDTH, (sprite/PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_HEIGHT, SPRITE_PAUSE_WIDTH, SPRITE_PAUSE_HEIGHT }, FRAME_DURATION);
    m_bottomPauseAnimation.addFrame(m_animBottomPauseTexture, { (sprite%PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_WIDTH, (sprite/PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_HEIGHT, SPRITE_PAUSE_WIDTH, SPRITE_PAUSE_HEIGHT }, FRAME_DURATION);
    m_topPauseAnimation.addFrame(m_animTopPauseTexture, { (sprite%PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_WIDTH, (sprite/PAUSE_SPRITES_PER_LINE) * SPRITE_PAUSE_HEIGHT, SPRITE_PAUSE_WIDTH, SPRITE_PAUSE_HEIGHT }, FRAME_DURATION);
  }

  // Create the physical body
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(AREA_WIDTH / 2.0f / BOX2D_PIXELS_PER_METER, AREA_HEIGHT / 2.0f / BOX2D_PIXELS_PER_METER);

  // Body
  b2CircleShape b2_circle;
  b2_circle.m_radius = CHARACTER_WIDTH * 0.4f / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixtureDef;
  b2_fixtureDef.shape = &b2_circle;

  // Create the body of character
  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_targets.push_back(new Target(Origin::CHARACTER, false, this));
  m_body->CreateFixture(&b2_fixtureDef)->SetUserData(m_targets.back());

  // Create the hitbox of player
  float radius = CHARACTER_WIDTH / BOX2D_PIXELS_PER_METER;
  b2Vec2 vertices[8];
  vertices[0].Set(0,0);
  for (int i = 0; i < 7; i++) {
      float angle = ((i / 6.0f * 90.0f) - 45.0f) * DEGTORAD;
      vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
  }
  b2PolygonShape b2_polygonShape;
  b2_polygonShape.Set(vertices, 8);
  b2_fixtureDef.shape = &b2_polygonShape;
  b2_fixtureDef.isSensor = true;
  m_targets.push_back(new Target(Origin::CHARACTER, true, this));
  m_body->CreateFixture(&b2_fixtureDef)->SetUserData(m_targets.back());

  // Register event
  events.registerHandler<EnemyDeathEvent>(&Character::onEnemyDeathEvent, this);
}

Character::~Character() {
  m_body->GetWorld()->DestroyBody(m_body);

  for (auto target: m_targets) {
    delete target;
  }
}

void Character::update(const float dt) {
    // if the attack is not ready to use, the actual cooldown reduce
    if(m_timeElapsedAttack<m_attackPeriod)
    {
        m_timeElapsedAttack+=dt;
    }
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

  // Set the right animation
  // Angle in RAD
  float angle = m_body->GetAngle();

  // If the player move
  if (m_body->GetLinearVelocity().x != 0 || m_body->GetLinearVelocity().y != 0) {
    // If the character is oriented to left
    if (angle >= 150.0f * DEGTORAD || angle < -150.0f * DEGTORAD) {
      m_currentAnimation = &m_leftAnimation;
    }
    // If the character is oriented to right
    else if (angle >= -30.0f * DEGTORAD && angle < 30.0f * DEGTORAD) {
      m_currentAnimation = &m_rightAnimation;
    }
    // If the character is oriented to the top
    else if (angle >= -150.0f * DEGTORAD && angle < -30.0f * DEGTORAD)
    {
      m_currentAnimation = &m_topAnimation;
    }
    // If the character is oriented to the bottom
    else if (angle >= 30.0f * DEGTORAD && angle < 150.0f * DEGTORAD)
    {
      m_currentAnimation = &m_bottomAnimation;
    }
  }
  // If player was stopped
  else {
    if (angle >= 150.0f * DEGTORAD || angle < -150.0f * DEGTORAD) {
      m_currentAnimation = &m_leftPauseAnimation;
    }
    // If the character is oriented to right
    else if (angle >= -30.0f * DEGTORAD && angle < 30.0f * DEGTORAD) {
      m_currentAnimation = &m_rightPauseAnimation;
    }
    // If the character is oriented to the top
    else if (angle >= -150.0f * DEGTORAD && angle < -30.0f * DEGTORAD)
    {
      m_currentAnimation = &m_topPauseAnimation;
    }
    // If the character is oriented to the bottom
    else if (angle >= 30.0f * DEGTORAD && angle < 150.0f * DEGTORAD)
    {
      m_currentAnimation = &m_bottomPauseAnimation;
    }
  }

  // Update animation
  if (m_currentAnimation != nullptr) {
    m_currentAnimation->update(dt);
  }

  // Set direction move
  //m_spriteDirection = m_verticalDirection | m_horizontalDirection;

  // Reset move
  m_verticalDirection = Direction::NONE;
  m_horizontalDirection = Direction::NONE;

  // Trigger location event
  CharacterLocationEvent event;
  event.pos = {m_body->GetPosition().x, m_body->GetPosition().y};
  m_events.triggerEvent(&event);

  // Trigger stats event
  CharacterStatsEvent statsEvent;
  statsEvent.characterHealth=(int)m_health;
  statsEvent.characterMaxHealth=(int)m_maxHealth;
  statsEvent.characterGold=m_gold;
  statsEvent.characterDamage=(int)m_damage;
  statsEvent.characterArmor=(int)m_armor;
  statsEvent.characterRegenValue=(int)m_regenerationValue;
  statsEvent.characterRegenRate=(int)m_regenerationRate;
  m_events.triggerEvent(&statsEvent);

  // Trigger movement event
  CharacterMovementEvent moveEvent;
  moveEvent.moves = b2_velocity.x || b2_velocity.y;
  m_events.triggerEvent(&moveEvent);

  // The player regenerate health over time
  m_health+=((m_regenerationValue/m_regenerationRate)*dt);

  // If the player actual health is above his max health, set it to his max health
  if(m_health>m_maxHealth)
  {
    m_health=m_maxHealth;
  }
  // Check if the player is still alive
  if(m_health<1.0f)
  {
    m_health = 0;
    this->death();
  }
}

void Character::render(sf::RenderWindow& window) {
  // Get box2d position
  b2Vec2 b2_pos = m_body->GetPosition();

  // Angle in RAD
  float angle = m_body->GetAngle();

  if (m_currentAnimation != nullptr) {
    m_currentAnimation->renderAt(window, { b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER - CHARACTER_HEIGHT * CHARACTER_HEIGHT_SCALE * 2.0f},0.0f,sf::Vector2f(CHARACTER_WIDTH_SCALE, CHARACTER_HEIGHT_SCALE));
  }
  else {
    // Display the character
    sf::CircleShape circle;
    circle.setOrigin(CHARACTER_WIDTH * 0.4f, CHARACTER_WIDTH * 0.4f);
    circle.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
    circle.setRadius(CHARACTER_WIDTH * 0.4f);
    circle.setFillColor(sf::Color::Black);
    window.draw(circle);

    // Orientation of character
    sf::RectangleShape rect({CHARACTER_WIDTH * 0.80f, 4.0f});
    rect.setOrigin(CHARACTER_WIDTH * 0.4f, 2.0f);
    rect.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
    rect.setFillColor(sf::Color::Red);
    rect.setRotation(angle * 180 / M_PI);
    window.draw(rect);
  }
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
  sf::Vector2i center(b2_pos.x*BOX2D_PIXELS_PER_METER,
                      b2_pos.y*BOX2D_PIXELS_PER_METER);
  float newAngle(0)
    , dist( std::hypot( mousePos.x - center.x, mousePos.y - center.y) );

  newAngle = (( mousePos.y < center.y ) ? -1 : 1)
    * acos((mousePos.x-center.x)/dist);

  m_body->SetTransform(b2_pos, newAngle);

  // Store cursor's position for Box2D and drawing usage
  m_target.x = mousePos.x / (double)BOX2D_PIXELS_PER_METER;
  m_target.y = mousePos.y / (double)BOX2D_PIXELS_PER_METER;
}

void Character::simpleAttack()
{
    if(m_timeElapsedAttack>=m_attackPeriod)
    {
        if (m_visibleEnemies.size()) {
          for (Enemy* enemy: m_visibleEnemies)
          {
              enemy->substractToHealth((m_damage-enemy->getArmor()));
          }
          m_timeElapsedAttack-=m_attackPeriod;
          
          CharacterHitEnemyEvent hitEnemyEvent;
          hitEnemyEvent.numberOfHits = m_visibleEnemies.size();
          m_events.triggerEvent(&hitEnemyEvent);
        }
    }
}

void Character::buyDamage()
{
    if(m_gold>=20)
    {
        m_gold-=20;
        m_damage++;
    }
}

void Character::buyMaxHealth()
{
    if(m_gold>=5)
    {
        m_gold-=5;
        m_maxHealth++;
    }
}

void Character::buyRegenValue()
{
    if(m_gold>=30)
    {
        m_gold-=30;
        m_regenerationValue++;
    }
}

void Character::setMaxHealth(float maxHealth) {
  m_maxHealth=maxHealth;
}

float Character::getMaxHealth() const {
  return m_maxHealth;
}

void Character::addToMaxHealth(float value)
{
    m_maxHealth+=value;
}

void Character::substractToMaxHealth(float value)
{
    m_maxHealth-=value;
}

void Character::setHealth(float health) {
  m_health=health;
}

float Character::getHealth() const {
  return m_health;
}

void Character::addToHealth(float value)
{
    m_health+=value;
}

void Character::substractToHealth(float value)
{
    m_health-=value;
    EnemyHitCharacterEvent hitEvent;
    hitEvent.damages = value;
    m_events.triggerEvent(&hitEvent);
}

void Character::setArmor(float armor)
{
    m_armor=armor;
}

int Character::getArmor() const
{
    return m_armor;
}

void Character::setGold(int gold)
{
    m_gold=gold;
}

int Character::getGold() const
{
    return m_gold;
}

void Character::addToGold(int value)
{
    m_gold+=value;
}

void Character::substractToGold(int value)
{
    m_gold-=value;
}

void Character::acquiredEnemy(Enemy* enemy) {
  m_visibleEnemies.insert(enemy);
}

void Character::lostEnemy(Enemy* enemy) {
  m_visibleEnemies.erase(enemy);
}

void Character::death()
{
  CharacterDeathEvent deathEvent;
  m_events.triggerEvent(&deathEvent);

  m_body->GetWorld()->DestroyBody(m_body);
  kill();
}

game::EventStatus Character::onEnemyDeathEvent(game::EventType type, game::Event *event)
{
    auto deathEvent = static_cast<EnemyDeathEvent *>(event);

    this->addToGold(deathEvent->givenGold);

    return game::EventStatus::KEEP;
}
