/*
 * Copyright (c) 2014-2015, Julien Bernard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef GAME_ENTITY_MANAGER_H
#define GAME_ENTITY_MANAGER_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace game {

  /**
   * @ingroup graphics
   */
  class EntityManager {
  public:

    void update(float dt);
    void render(sf::RenderWindow& window);

    void addEntity(Entity& e);
    Entity *removeEntity(Entity *e);

    template<typename E>
    E *removeTypedEntity(E *e) {
      static_assert(std::is_base_of<Entity, E>::value, "E must be an Entity");
      return static_cast<E*>(removeEntity(e));
    }

  private:
    std::vector<Entity *> m_entities;
  };


}


#endif // GAME_ENTITY_MANAGER_H
