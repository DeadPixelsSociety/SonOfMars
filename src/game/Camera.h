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
#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @ingroup graphics
   */
  class Camera {
  public:
    ~Camera();
    virtual void update(sf::Event& event) = 0;
    virtual void configure(sf::RenderWindow& window) = 0;
  };

  /**
   * @ingroup graphics
   */
  class CameraManager {
  public:
    void addCamera(Camera& camera);
    void update(sf::Event& event);
  private:
    std::vector<Camera*> m_cameras;
  };

  /**
   * @ingroup graphics
   */
  class SceneCamera : public Camera {
  public:
    SceneCamera(float width, const sf::Vector2f& center);

    float getWidth() const {
      return m_width;
    }

    void setWidth(float width) {
      m_width = width;
    }

    const sf::Vector2f& getCenter() const {
      return m_center;
    }

    void setCenter(const sf::Vector2f& center) {
      m_center = center;
    }

  private:
    float m_width;
    sf::Vector2f m_center;
  };

  /**
   * @ingroup graphics
   */
  class FixedRatioCamera : public SceneCamera {
  public:
    FixedRatioCamera(float width, float height, const sf::Vector2f& center = sf::Vector2f(0.0f, 0.0f));
    virtual void update(sf::Event& event) override;
    virtual void configure(sf::RenderWindow& window) override;

  private:
    float m_ratio;
    sf::View m_view;
  };

  /**
   * @ingroup graphics
   */
  class FlexibleCamera : public SceneCamera {
  public:
    FlexibleCamera(float width, const sf::Vector2f& center = sf::Vector2f(0.0f, 0.0f));
    virtual void update(sf::Event& event) override;
    virtual void configure(sf::RenderWindow& window) override;

  private:
    sf::View m_view;
  };

  /**
   * @ingroup graphics
   */
  class HeadsUpCamera : public Camera {
  public:
    HeadsUpCamera(sf::RenderWindow& window);
    virtual void update(sf::Event& event) override;
    virtual void configure(sf::RenderWindow& window) override;

  private:
    sf::View m_view;
  };

}

#endif // GAME_CAMERA_H
