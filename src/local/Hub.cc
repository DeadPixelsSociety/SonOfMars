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

#include "Hub.h"

#include <cassert>

#include "local/config.h"


Hub::Hub(game::EventManager& events, game::ResourceManager& resources)
: m_timeElapsed(0.0f)
, m_font(nullptr)
{
    m_font=resources.getFont("../share/capitalis_goreanis.ttf");
    assert(m_font!=nullptr);
    m_StrHealth.setFont(*m_font);
    m_StrHealth.setString("100");
    m_StrHealth.setCharacterSize(20);
    m_StrHealth.setColor(sf::Color::Red);
    m_StrHealth.setPosition(100.0f,100.0f);
}
Hub::~Hub()
{

}
void Hub::update(const float dt)
{

}
void Hub::render(sf::RenderWindow& window)
{
    window.draw(m_StrHealth);
}
void Hub::setStrHealth(int health)
{

}
