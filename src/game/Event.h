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
#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <functional>
#include <string>

#include "Id.h"

namespace game {
  /**
   * @ingroup base
   */
  typedef Id EventType;

#define INVALID_EVENT INVALID_ID

  /**
   * @ingroup base
   */
  struct Event {
    static const EventType type = INVALID_EVENT;
  };

  /**
   * @ingroup base
   */
  enum class EventStatus {
    KEEP, /**< The handler must be kept */
    DIE,  /**< The handler can be removed */
  };

  /**
   * @ingroup base
   */
  typedef std::function<EventStatus(EventType, Event *)> EventHandler;

}

constexpr game::EventType operator"" _type(const char *str, std::size_t sz) {
  return game::Hash(str, sz, sz);
}

#endif // GAME_EVENT_H
