#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>
#include "Entity.h"

static constexpr float BOX2D_SCALE = 0.01f;

class Character: public Entity
{
    public:
        Character(b2World &b2_world);

        virtual void update(const float dt) override;
        virtual void render(sf::RenderWindow& window) override;
        
    private:
        b2Body *m_body; 

};
#endif //CHARACTER_H