#include "Enemy.h"

#include "local/config.h"

static constexpr float VELOCITY_STEP = 5.0f;

Enemy::Enemy(b2World &b2_world, b2Vec2 position, Character &hero)
: m_body(nullptr)
, m_hero(hero){
  b2BodyDef b2_bodyDef;
  b2_bodyDef.type = b2_dynamicBody;
  b2_bodyDef.position.Set(AREA_WIDTH / 4.0f / BOX2D_PIXELS_PER_METER, AREA_HEIGHT / 4.0f / BOX2D_PIXELS_PER_METER);

  b2CircleShape b2_circle;
  b2_circle.m_radius = CHARACTER_WIDTH / BOX2D_PIXELS_PER_METER;

  b2FixtureDef b2_fixture;
  b2_fixture.shape = &b2_circle;

  m_body = b2_world.CreateBody(&b2_bodyDef);
  m_body->CreateFixture(&b2_fixture);
}

void Enemy::update(const float dt) {
  // Manage the move
  
  /*b2Vec2 b2_velocity = m_body->GetLinearVelocity();
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

  m_body->SetLinearVelocity(b2_velocity);

  // Reset move
  m_verticalDirection = Direction::NONE;
  m_horizontalDirection = Direction::NONE;

  // Angle
*/
}

void Enemy::render(sf::RenderWindow& window) {
  sf::CircleShape circle;
  b2Vec2 b2_pos = m_body->GetPosition();
  circle.setOrigin(CHARACTER_WIDTH, CHARACTER_WIDTH);
  circle.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  circle.setRadius(CHARACTER_WIDTH);
  circle.setFillColor(sf::Color::Cyan);
  window.draw(circle);

  // Orientation of character
  float angle = m_body->GetAngle();
  // m_body->SetAngle(1.6f);
  sf::RectangleShape rect({CHARACTER_WIDTH * 2.0f, 4.0f});
  rect.setOrigin(CHARACTER_WIDTH, 2.0f);
  rect.setPosition(b2_pos.x * BOX2D_PIXELS_PER_METER, b2_pos.y * BOX2D_PIXELS_PER_METER);
  rect.setFillColor(sf::Color::Red);
  rect.setRotation(angle * 180 / 3.14);
  window.draw(rect);
  
  // Target replacing mouse cursor
  
}