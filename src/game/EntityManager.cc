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
#include "EntityManager.h"

#include <cassert>
#include <algorithm>
#include <memory>

namespace game {

  void EntityManager::update(float dt) {
    // erase-remove idiom
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](const Entity *e) {
      return !e->isAlive();
    }), m_entities.end());

    std::sort(m_entities.begin(), m_entities.end(), [](const Entity * e1, const Entity * e2) {
      return e1->getPriority() < e2->getPriority();
    });

    for (auto entity : m_entities) {
      entity->update(dt);
    }
  }

  void EntityManager::render(sf::RenderWindow& window) {
    for (auto entity : m_entities) {
      entity->render(window);
    }
  }

  void EntityManager::addEntity(Entity& e) {
    m_entities.push_back(&e);
  }

  Entity *EntityManager::removeEntity(Entity *e) {
    // erase-remove idiom
    auto it = std::remove(m_entities.begin(), m_entities.end(), e);

    if (it != m_entities.end()) {
      m_entities.erase(it, m_entities.end());
      return e;
    }

    return nullptr;
  }

}
