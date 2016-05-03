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

#ifndef STAGE_H
#define STAGE_H

#include <Box2D/Box2D.h>

#include <game/Camera.h>
#include <game/Entity.h>
#include <game/Random.h>
#include <game/ResourceManager.h>
#include <game/WindowGeometry.h>

#include <game/Camera.h>
#include <game/EventManager.h>

#include "Arena.h"
#include "EnemyManager.h"
#include "NotificationManager.h"

class Stage: public game::Entity {
public:
  enum Place {
    ARENA,
    SAFE_ROOM,
  };

public: 
  Stage(b2World &b2_world, game::ResourceManager &resources, game::CameraManager &cameras, game::EventManager& events, game::Random random, game::WindowGeometry& geometry, float stageWidth, float stageHeight, float flexibleCameraWidth);

  sf::View getCurrentView() const;
  void togglePlace();
  void configureCurrentCamera(sf::RenderWindow &window);
  game::EventStatus onCharacterLocationEvent(game::EventType type, game::Event *event);
  game::EventStatus onEndWaveEvent(game::EventType type, game::Event *event);

  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  Place m_currentPlace;
  game::FlexibleCamera m_arenaCamera;
  game::FixedRatioCamera m_shopCamera;
  Arena m_arena;
  EnemyManager m_enemies;
  NotificationManager m_notifs;
};

#endif // STAGE_H
