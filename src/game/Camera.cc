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
#include "Camera.h"

namespace game {

  Camera::~Camera() {
    // nothing
  }

  void CameraManager::addCamera(Camera& camera) {
    m_cameras.push_back(&camera);
  }

  void CameraManager::update(sf::Event& event) {
    for (auto camera : m_cameras) {
      camera->update(event);
    }
  }


  SceneCamera::SceneCamera(float width, const sf::Vector2f& center)
  : m_width(width)
  , m_center(center)
  {
  }


  FixedRatioCamera::FixedRatioCamera(float width, float height, const sf::Vector2f& center)
  : SceneCamera(width, center)
  , m_ratio(width / height)
  , m_view(center, { width, height })
  {
  }

  void FixedRatioCamera::update(sf::Event& event) {
    if (event.type != sf::Event::Resized) {
      return;
    }

    float w = static_cast<float>(event.size.width);
    float h = static_cast<float>(event.size.height);

    float r = w / h / m_ratio;

    sf::FloatRect vp;

    if (r < 1.0f) {
      vp.left = 0.0f;
      vp.width = 1.0;

      vp.top = (1 - r) / 2;
      vp.height = r;
    } else {
      vp.top = 0.0f;
      vp.height = 1.0f;

      vp.left = (1 - 1 / r) / 2;
      vp.width = 1 / r;
    }

    m_view.setViewport(vp);
  }

  void FixedRatioCamera::configure(sf::RenderWindow& window) {
    m_view.setCenter(getCenter());
    window.setView(m_view);
  }


  FlexibleCamera::FlexibleCamera(float width, const sf::Vector2f& center)
  : SceneCamera(width, center)
  {

  }

  void FlexibleCamera::update(sf::Event& event) {
    if (event.type != sf::Event::Resized) {
      return;
    }

    float w = static_cast<float>(event.size.width);
    float h = static_cast<float>(event.size.height);

    float height = getWidth() / w * h;

    m_view.setSize(getWidth(), height);
  }

  void FlexibleCamera::configure(sf::RenderWindow& window) {
    m_view.setCenter(getCenter());
    window.setView(m_view);
  }


  HeadsUpCamera::HeadsUpCamera(sf::RenderWindow& window) {
    m_view = window.getDefaultView();
  }

  void HeadsUpCamera::update(sf::Event& event) {
    if (event.type != sf::Event::Resized) {
      return;
    }

    float w = static_cast<float>(event.size.width);
    float h = static_cast<float>(event.size.height);

    m_view.reset({ 0.0f, 0.0f, w, h });
  }

  void HeadsUpCamera::configure(sf::RenderWindow& window) {
    window.setView(m_view);
  }

}
