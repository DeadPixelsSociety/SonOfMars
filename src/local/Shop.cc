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

#include <iostream>

#include "local/config.h"

#include "Shop.h"


void Shop::render(sf::RenderWindow& window) {
  sf::RectangleShape rect(sf::Vector2f(SHOP_WIDTH, SHOP_HEIGHT));
  //rect.setColor(sf::Color(0, 255, 0));
  rect.setFillColor(sf::Color::Green);

  rect.setPosition({SHOP_OFFSET_X, 0.0f});
  window.draw(rect);
  /*sf::Sprite sprite;
  sprite.setTexture(*m_background);
  sprite.setScale(AREA_WIDTH / 3000.0f, AREA_HEIGHT / 1688.0f);
  window.draw(sprite);*/
}
