#include "Character.h"

Character::Character(b2World &b2_world)
: Entity(1)
, m_body(nullptr)
{
    b2BodyDef b2_bodyDef;
    b2_bodyDef.type = b2_dynamicBody;
    b2_bodyDef.position.Set(100.0f * BOX2D_SCALE, 100.0f * BOX2D_SCALE);
    b2CircleShape b2_circle;
    b2_circle.m_radius = 100.0f * BOX2D_SCALE;
    b2FixtureDef b2_fixture;
    b2_fixture.shape = &b2_circle;
    m_body = b2_world.CreateBody(&b2_bodyDef);
    m_body->CreateFixture(&b2_fixture);
}


void Character::update(const float dt)
{

}

void Character::render(sf::RenderWindow& window)
{
    sf::CircleShape circle;
    circle.setPosition(100,100);
    circle.setRadius(10);
    circle.setFillColor(sf::Color::White);
    window.draw(circle);
}
