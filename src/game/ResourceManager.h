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
#ifndef GAME_RESOURCE_MANAGER_H
#define GAME_RESOURCE_MANAGER_H

#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "AssetManager.h"

namespace game {

  /**
   * @ingroup graphics
   */
  class ResourceManager : public AssetManager {
  public:
    sf::Font *getFont(const boost::filesystem::path& path);
    sf::SoundBuffer *getSoundBuffer(const boost::filesystem::path& path);
    sf::Texture *getTexture(const boost::filesystem::path& path);

  private:
    template<typename T>
    class ResourceCache {
    public:
      T *findResource(const boost::filesystem::path& key);
      T *loadResource(const boost::filesystem::path& key, const boost::filesystem::path& path);
    private:
      std::map<boost::filesystem::path, std::unique_ptr<T>> m_cache;
    };

  private:
    ResourceCache<sf::Font> m_fonts;
    ResourceCache<sf::SoundBuffer> m_sounds;
    ResourceCache<sf::Texture> m_textures;

  private:
    template<typename T>
    T *getResource(const boost::filesystem::path& path, ResourceCache<T>& cache);
  };

}

#endif // GAME_RESOURCE_MANAGER_H
