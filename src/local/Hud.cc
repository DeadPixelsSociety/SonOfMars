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

#include "Hud.h"

#include <cassert>
#include <stdlib.h>

#include "local/config.h"


Hud::Hud(game::EventManager& events, game::ResourceManager& resources)
: m_timeElapsed(0.0f)
, m_font(nullptr)
, m_CharacterHealth(0)
{
    m_font=resources.getFont("capitalis_goreanis.ttf");
    assert(m_font!=nullptr);
    m_StrHealth.setFont(*m_font);
    std::string str="Health: "+std::to_string(m_CharacterHealth);
    m_StrHealth.setString(str);
    m_StrHealth.setCharacterSize(25);
    m_StrHealth.setColor(sf::Color::Red);
    m_StrHealth.setPosition(100.0f,0.0f);
    // Register event
    events.registerHandler<CharacterHealthEvent>(&Hud::onCharacterHealthEvent, this);
}
Hud::~Hud()
{

}
void Hud::update(const float dt)
{
    m_StrHealth.setString("Health: "+std::to_string(m_CharacterHealth));
}
void Hud::render(sf::RenderWindow& window)
{
    window.draw(m_StrHealth);
}
game::EventStatus Hud::onCharacterHealthEvent(game::EventType type, game::Event *event)
{
    auto healthEvent = static_cast<CharacterHealthEvent *>(event);

    m_CharacterHealth = healthEvent->CharacterHealth;

    return game::EventStatus::KEEP;
}
