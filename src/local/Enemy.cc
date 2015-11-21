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

#include "Enemy.h"

#include <cmath>

#include "local/config.h"

#include "Character.h"
#include "Game.h"
#include "Target.h"

static constexpr int BASIC_HEALTH = 5;
static constexpr int BASIC_DAMAGE = 1;
static constexpr int BASIC_ARMOR = -1;
static constexpr int BASIC_EXP = 2;
static constexpr float BASIC_SPEED = 3.1f;
static constexpr float BASIC_ATTACKPERIOD = 3.0f;
static constexpr float DEGTORAD = M_PI / 180.0f;

Enemy::Enemy(b2World &b2_world, game::EventManager& events, sf::Vector2f position,float multiplier)
: m_body(nullptr)
, m_target({0.0f, 0.0f})
, m_events(events)
, m_health(BASIC_HEALTH*multiplier)
, m_damage(BASIC_DAMAGE*multiplier)
, m_armor(BASIC_ARMOR+multiplier)
, m_expGiven(BASIC_EXP*multiplier)
, m_speed(BASIC_SPEED+(multiplier/10.0f))
, m_attackPeriod(BASIC_ATTACKPERIOD-(multiplier/10.0f))
, m_timeElapsed(BASIC_ATTACKPERIOD-1.0f)
 {
  // Register events trigger
  events.registerHandler<CharacterLocationEvent>(&Enemy::onCharacterLocationEvent, this);

  // Set the initial position
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(position.x / BOX2D_PIXELS_PER_METER, position.y / BOX2D_PIXELS_PER_METER);

  b2CircleShape b2_circle;
  b2_circle.m_radius = ENEMY_WIDTH / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;

  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_targets.push_back(new Target(Origin::ENEMY, false, this));
  m_body->CreateFixture(&b2_fixture)->SetUserData(m_targets.back());

  // Create the hitbox of the ennemy
  float radius = 1.0f;
  b2Vec2 vertices[8];
  vertices[0].Set(0,0);
  for (int i = 0; i < 7; i++) {
      float angle = ((i / 6.0f * 90.0f) - 45.0f) * DEGTORAD;
      vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
  }
  b2PolygonShape b2_polygonShape;
  b2_polygonShape.Set(vertices, 8);
  b2_fixture.shape = &b2_polygonShape;
  b2_fixture.isSensor = true;
  m_targets.push_back(new Target(Origin::ENEMY, true, this));
  m_body->CreateFixture(&b2_fixture)->SetUserData(m_targets.back());
}

Enemy::~Enemy() {
  for (auto target: m_targets) {
    delete target;
  }
}

void Enemy::update(const float dt) {
    m_timeElapsed += dt;
  // Manage the move
  // Compute enemy's rotation
  b2Vec2 dir = m_target - m_body->GetPosition();
  float norm = std::hypot(dir.x, dir.y);
  m_body->SetTransform(m_body->GetPosition(),
    (( dir.y < 0 ) ? -1 : 1) * acos( dir.x/norm) );
  // Set enemy's speed (constant)
  if ( norm > 3.0f*ENEMY_WIDTH / BOX2D_PIXELS_PER_METER )
    m_body->SetLinearVelocity((m_speed/norm)*dir);
  else // Useless when other enemies push
    m_body->SetLinearVelocity( b2Vec2(0,0) );

    if(m_timeElapsed>=m_attackPeriod)
    {
        //Manage the attacks
        if(!m_visibleCharacter.empty())
        {
            this->simpleAttack();
        }
        m_timeElapsed-=m_attackPeriod;
    }
    //check if the enemy has health>0
    if(m_health<=0)
    {
        // Trigger death event
        EnemyDeathEvent deathEvent;
        deathEvent.givenExperience=m_expGiven;
        m_events.triggerEvent(&deathEvent);
        this->death();
    }
}

void Enemy::render(sf::RenderWindow& window) {
  sf::CircleShape circle;
  b2Vec2 b2_pos = m_body->GetPosition();
  circle.setOrigin(ENEMY_WIDTH, ENEMY_WIDTH);
  circle.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  circle.setRadius(ENEMY_WIDTH);
  circle.setFillColor(sf::Color::Cyan);
  window.draw(circle);

  // Orientation of enemy
  float angle = m_body->GetAngle();
  sf::RectangleShape rect({ENEMY_WIDTH * 2.0f, 4.0f});
  rect.setOrigin(ENEMY_WIDTH, 2.0f);
  rect.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  rect.setFillColor(sf::Color::Red);
  rect.setRotation(angle * 180 / M_PI);
  window.draw(rect);
}

void Enemy::death() {
  m_body->GetWorld()->DestroyBody(m_body);
  kill();
}

game::EventStatus Enemy::onCharacterLocationEvent(game::EventType type, game::Event *event) {
  auto locationEvent = static_cast<CharacterLocationEvent *>(event);

  m_target = locationEvent->pos;

  return game::EventStatus::KEEP;
}
void Enemy::acquiredCharacter(Character* character) {
  m_visibleCharacter.insert(character);
}

void Enemy::lostCharacter(Character* character) {
  m_visibleCharacter.erase(character);
}
void Enemy::setHealth(int health) {
  m_health=health;
}

int Enemy::getHealth() const {
  return m_health;
}
void Enemy::addToHealth(int value)
{
    m_health+=value;
}
void Enemy::substractToHealth(int value)
{
    m_health-=value;
}
void Enemy::setArmor(int armor)
{
    m_armor=armor;
}
int Enemy::getArmor() const
{
    return m_armor;
}
void Enemy::simpleAttack()
{
    for(Character* character: m_visibleCharacter)
    {
        character->substractToHealth(m_damage-character->getArmor());
    }
}
