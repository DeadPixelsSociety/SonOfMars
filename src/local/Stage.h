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

#include <game/Camera.h>
#include <game/EventManager.h>

class Stage {
public:
  enum Place {
    ARENA,
    SAFE_ROOM,
  };

public: 
  Stage(game::CameraManager &cameras, game::EventManager& events, float stageWidth, float stageHeight, float flexibleCameraWidth);

  sf::View getCurrentView() const;
  void togglePlace();
  void configureCurrentCamera(sf::RenderWindow &window);
  game::EventStatus onCharacterLocationEvent(game::EventType type, game::Event *event);

private:
  Place m_currentPlace;
  game::FlexibleCamera m_arenaCamera;
  game::FixedRatioCamera m_shopCamera;
};

#endif // STAGE_H
