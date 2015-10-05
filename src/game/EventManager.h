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
#ifndef GAME_EVENT_MANAGER_H
#define GAME_EVENT_MANAGER_H

#include <map>
#include <vector>

#include "Event.h"

namespace game {

  /**
   * @ingroup base
   */
  typedef uint64_t EventHandlerId;

  /**
   * @ingroup base
   */
  class EventManager {
  public:
    EventManager();

    EventHandlerId registerHandler(EventType type, EventHandler handler);

    template<typename E>
    EventHandlerId registerHandler(EventHandler handler) {
      static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
      static_assert(E::type != INVALID_EVENT, "E must define its type");
      return registerHandler(E::type, handler);
    }

    template<typename R, typename T>
    EventHandlerId registerHandler(EventType type, R T::*pm, T *obj) {
      return registerHandler(type, std::bind(pm, obj, std::placeholders::_1, std::placeholders::_2));
    }

    template<typename E, typename R, typename T>
    EventHandlerId registerHandler(R T::*pm, T *obj) {
      static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
      static_assert(E::type != INVALID_EVENT, "E must define its type");
      return registerHandler(E::type, std::bind(pm, obj, std::placeholders::_1, std::placeholders::_2));
    }

    void removeHandler(EventHandlerId id);

    void removeHandlers(std::initializer_list<EventHandlerId> ids) {
      for (auto id : ids) {
        removeHandler(id);
      }
    }

    void triggerEvent(EventType type, Event *event);

    template<typename E>
    void triggerEvent(E *event) {
      static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
      static_assert(E::type != INVALID_EVENT, "E must define its type");
      triggerEvent(E::type, event);
    }

  private:
    struct Handler {
      EventHandlerId id;
      EventHandler handler;
    };

    EventHandlerId m_current_id;
    std::map<EventType, std::vector<Handler>> m_handlers;
  };

}

#endif // GAME_EVENT_MANAGER_H
