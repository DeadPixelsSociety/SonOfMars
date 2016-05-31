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

#ifndef SHOP_H
#define SHOP_H

#include <game/Entity.h>
#include "local/config.h"

class Shop: public game::Entity {
public:
  //Shop(b2World &b2_world, game::ResourceManager &resources);

  /*Shop(const Shop&) = delete;
  Shop& operator=(const Shop&) = delete;

  Shop(Shop&&) = delete;
  Shop& operator=(Shop&&) = delete;*/

  virtual void render(sf::RenderWindow& window) override;

private:
  sf::Texture *m_background;

};

#endif // SHOP_H
