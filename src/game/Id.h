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
#ifndef GAME_ID_H
#define GAME_ID_H

#include <cstdint>

namespace game {

  /**
   * @ingroup base
   */
  typedef uint64_t Id;

#define INVALID_ID 0

  /**
   * @ingroup base
   *
   * The hash is a Fowler–Noll–Vo 1a hash.
   */
  constexpr Id Hash(const char *str, std::size_t sz, std::size_t idx) {
    return idx == 0 ? 0xcbf29ce484222325 : (str[idx - 1] ^ Hash(str, sz, idx - 1)) * 0x100000001b3;
  }

  /**
   * @ingroup base
   */
  inline Id Hash(const std::string& str) {
    return Hash(str.c_str(), str.size(), str.size());
  }

}

constexpr game::Id operator"" _id(const char *str, std::size_t sz) {
  return game::Hash(str, sz, sz);
}

#endif // GAME_ID_H
