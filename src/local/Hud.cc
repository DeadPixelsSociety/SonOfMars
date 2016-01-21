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


Hud::Hud(game::EventManager& events, game::ResourceManager& resources,game::WindowGeometry& geometry)
: m_geometry(geometry)
, m_timeElapsed(0.0f)
, m_font(nullptr)
, m_characterMaxHealth(0)
, m_characterHealth(0)
, m_characterGold(0)
, m_characterDamage(0)
, m_characterArmor(0)
, m_characterRegenValue(0)
, m_characterRegenRate(0)
, m_display(false)
{
    m_font=resources.getFont("GRECOromanLubedWrestling.ttf");
    assert(m_font!=nullptr);
    // Register event
    events.registerHandler<CharacterStatsEvent>(&Hud::onCharacterStatsEvent, this);
}
Hud::~Hud()
{

}
void Hud::update(const float dt)
{
}
void Hud::render(sf::RenderWindow& window)
{
    if(m_display==true)
    {
        sf::RectangleShape baseHud;
        baseHud.setFillColor(sf::Color(0,0,0,128));
        baseHud.setPosition(sf::Vector2f(0.0f,0.0f));
        baseHud.setSize({m_geometry.getXFromRight(0),m_geometry.getYRatio(0.05f,0.0f)});

        sf::Text strHealth;
        //Set the characteristics of strHealth
        strHealth.setFont(*m_font);
        strHealth.setCharacterSize(25);
        strHealth.setColor(sf::Color::Red);
        strHealth.setPosition(0.0f,0.0f);
        strHealth.setString("Health: "+std::to_string(m_characterHealth)+"/"+std::to_string(m_characterMaxHealth)+" (A)");

        sf::Text strGold;
        //Set the characteristics of strGold
        strGold.setFont(*m_font);
        strGold.setCharacterSize(25);
        strGold.setColor(sf::Color::Green);
        strGold.setPosition(250.0f,0.0f);
        strGold.setString("Sesterces: "+std::to_string(m_characterGold));

        sf::Text strDamage;
        //Set the characteristics of strDamage
        strDamage.setFont(*m_font);
        strDamage.setCharacterSize(25);
        strDamage.setColor(sf::Color::Blue);
        strDamage.setPosition(400.0f,0.0f);
        strDamage.setString("Damages: "+std::to_string(m_characterDamage)+" (E)");

        sf::Text strArmor;
        //Set the characteristics of strDamage
        strArmor.setFont(*m_font);
        strArmor.setCharacterSize(25);
        strArmor.setColor(sf::Color::White);
        strArmor.setPosition(600.0f,0.0f);
        strArmor.setString("Armor: "+std::to_string(m_characterArmor));

        sf::Text strRegen;
        //Set the characteristics of strRegen
        strRegen.setFont(*m_font);
        strRegen.setCharacterSize(25);
        strRegen.setColor(sf::Color::Cyan);
        strRegen.setPosition(720.0f,0.0f);
        strRegen.setString("Regeneration: "+std::to_string(m_characterRegenValue)+" over "+std::to_string(m_characterRegenRate)+" seconds (R)");

        window.draw(baseHud);
        window.draw(strHealth);
        window.draw(strGold);
        window.draw(strDamage);
        window.draw(strArmor);
        window.draw(strRegen);
    }
}
game::EventStatus Hud::onCharacterStatsEvent(game::EventType type, game::Event *event)
{
    auto statsEvent = static_cast<CharacterStatsEvent *>(event);

    m_characterHealth = statsEvent->characterHealth;
    m_characterMaxHealth = statsEvent->characterMaxHealth;
    m_characterGold = statsEvent->characterGold;
    m_characterDamage = statsEvent->characterDamage;
    m_characterArmor = statsEvent->characterArmor;
    m_characterRegenValue = statsEvent->characterRegenValue;
    m_characterRegenRate = statsEvent->characterRegenRate;

    return game::EventStatus::KEEP;
}
void Hud::switchDisplay()
{
    if(m_display==true)
    {
        m_display=false;
    }
    else
    {
        m_display=true;
    }
}
