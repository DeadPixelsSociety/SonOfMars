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
#ifndef HUD_H
#define HUD_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <game/WindowGeometry.h>

#include "Character.h"
#include "Game.h"

class Hud: public game::Entity
{
    public:
        Hud(game::EventManager& events, game::ResourceManager& resource, game::WindowGeometry& geometry);
        virtual ~Hud();
        virtual void update(const float dt) override;
        virtual void render(sf::RenderWindow& window) override;
        game::EventStatus onCharacterStatsEvent(game::EventType type, game::Event *event);
        void switchDisplay();
    private:
        game::WindowGeometry &m_geometry;
        float m_timeElapsed;
        sf::Font *m_font;
        int m_characterMaxHealth;
        int m_characterHealth;
        int m_characterGold;
        int m_characterDamage;
        int m_characterArmor;
        int m_characterRegenValue;
        int m_characterRegenRate;
        bool m_display;
};
#endif //HUD_H
