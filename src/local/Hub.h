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
#ifndef HUB_H
#define HUB_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>

//#include "Game.h"

class Hub: public game::Entity
{
    public:
        Hub(game::EventManager& events, game::ResourceManager& resource);
        virtual ~Hub();
        virtual void update(const float dt) override;
        virtual void render(sf::RenderWindow& window) override;
        void setStrHealth(int health);
    private:
        sf::Text m_StrHealth;
        float m_timeElapsed;
        sf::Font *m_font;

};

#endif //HUB_H
