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
#ifndef GAME_SINGLETON_H
#define GAME_SINGLETON_H

#include <cassert>
#include <utility>

namespace game {

  template<typename T>
  class SingletonStorage;

  /**
   * @brief A singleton that wraps a pointer provided by a storage.
   *
   * This class should be used with a global variable. It acts as an access to
   * a singleton which storage is provided by a @c SingletonStorage<T>.
   *
   * ~~~{.cc}
   * game::Singleton<Foo> gFoo;
   *
   * int main() {
   *    game::SingletonStorage<Foo> fooStorage(gFoo);
   *
   *    gFoo().bar();
   * }
   * ~~~
   *
   * @sa SingletonStorage
   * @ingroup base
   */
  template<typename T>
  class Singleton {
  public:
    /**
     * @brief Default constructor.
     *
     * It initialize the underlying pointer to @c nullptr. The actual
     * initialization is done when the storage is allocated.
     */
    Singleton()
    : m_single(nullptr)
    {
    }

    /**
     * @brief Deleted copy constructor.
     */
    Singleton(const Singleton&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Singleton(Singleton&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    Singleton& operator=(const Singleton&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    Singleton& operator=(Singleton&&) = delete;

    /**
     * @brief Access the singleton.
     *
     * The access of the singleton must be done after a storage has been
     * provided. Otherwise, the behaviour is undefined (and may result in a
     * crash).
     *
     * @returns a reference to the stored singleton
     */
    T& operator()() {
      assert(m_single);
      return *m_single;
    }

  private:

    friend class SingletonStorage<T>;

    T *m_single;
  };

  /**
   * @brief A storage for a singleton.
   *
   * This class is a wrapper around an object of class @c T that should be
   * unique in the system. It works in cooperation with a global variable of
   * type @c Singleton<T>. The global variable is for the access of the object
   * while this class is for the storage of the object. The global variable is
   * initialized at the storage construction.
   *
   * ~~~{.cc}
   * game::Singleton<Foo> gFoo;
   *
   * int main() {
   *    game::SingletonStorage<Foo> fooStorage(gFoo);
   *
   *    gFoo().bar();
   * }
   * ~~~
   *
   * @sa Singleton
   * @ingroup base
   */
  template<typename T>
  class SingletonStorage {
  public:
    /**
     * @brief Construct a storage for a singleton.
     *
     *
     * @param ref a reference to a singleton (a global variable)
     * @param args arguments for the constructor of class @c T
     */
    template<typename ... Args>
    SingletonStorage(Singleton<T>& ref, Args&&... args)
    : m_storage(std::forward<Args>(args)...) {
      assert(ref.m_single == nullptr);
      ref.m_single = &m_storage;
    }

  private:
    T m_storage;
  };

}

#endif // GAME_SINGLETON_H
