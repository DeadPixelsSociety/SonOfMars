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
, m_characterMaxHealth(0)
, m_characterHealth(0)
, m_characterGold(0)
{
    m_font=resources.getFont("GRECOromanLubedWrestling.ttf");
    assert(m_font!=nullptr);
    //Set the strings
    std::string strHealth="Health: "+std::to_string(m_characterHealth)+"/"+std::to_string(m_characterMaxHealth);
    std::string strGold="Sesterces: "+std::to_string(m_characterGold);
    //Set the characteristics of m_strHealth
    m_strHealth.setFont(*m_font);
    m_strHealth.setString(strHealth);
    m_strHealth.setCharacterSize(25);
    m_strHealth.setColor(sf::Color::Red);
    m_strHealth.setPosition(100.0f,0.0f);
    //Set the characteristics of m_strExperience
    m_strGold.setFont(*m_font);
    m_strGold.setString(strGold);
    m_strGold.setCharacterSize(25);
    m_strGold.setColor(sf::Color::Green);
    m_strGold.setPosition(350.0f,0.0f);
    // Register event
    events.registerHandler<CharacterStatsEvent>(&Hud::onCharacterStatsEvent, this);
}
Hud::~Hud()
{

}
void Hud::update(const float dt)
{
    m_strHealth.setString("Health: "+std::to_string(m_characterHealth)+"/"+std::to_string(m_characterMaxHealth));
    m_strGold.setString("Sesterces: "+std::to_string(m_characterGold));
}
void Hud::render(sf::RenderWindow& window)
{
    window.draw(m_strHealth);
    window.draw(m_strGold);
}
game::EventStatus Hud::onCharacterStatsEvent(game::EventType type, game::Event *event)
{
    auto statsEvent = static_cast<CharacterStatsEvent *>(event);

    m_characterHealth =statsEvent->characterHealth;
    m_characterMaxHealth = statsEvent->characterMaxHealth;
    m_characterGold = statsEvent->characterGold;

    return game::EventStatus::KEEP;
}
