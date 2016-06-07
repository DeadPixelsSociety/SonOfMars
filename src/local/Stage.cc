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

#include "Stage.h"

#include <cassert>

#include "local/config.h"

#include "Game.h"

Stage::Stage(b2World &b2_world, game::ResourceManager &resources, game::CameraManager &cameras, game::EventManager& events, game::Random& random, game::WindowGeometry& geometry)
: m_currentPlace(Stage::ARENA)
, m_arenaCamera(1000.0f, {AREA_WIDTH * 0.5f, AREA_HEIGHT * 0.5f})
, m_shopCamera(SHOP_WIDTH, SHOP_HEIGHT, {SHOP_OFFSET_X + SHOP_WIDTH * 0.5f, SHOP_HEIGHT * 0.5f})
, m_arena(b2_world, resources)
, m_shop(b2_world)
, m_enemies(b2_world, events, random)
, m_notifs(events, resources, geometry) {
  // Register events trigger
  events.registerHandler<CharacterLocationEvent>(&Stage::onCharacterLocationEvent, this);
  events.registerHandler<EndWaveEvent>(&Stage::onEndWaveEvent, this);

  cameras.addCamera(m_arenaCamera);
  cameras.addCamera(m_shopCamera);
}

sf::View Stage::getCurrentView() const {
  switch (m_currentPlace) {
    case ARENA:
      return m_arenaCamera.getView();

    case SAFE_ROOM:
      return m_shopCamera.getView();

    default:
      assert(false);
  }
}

void Stage::togglePlace() {
  switch (m_currentPlace) {
    case ARENA:
      m_currentPlace = SAFE_ROOM;
      break;

    case SAFE_ROOM:
      m_currentPlace = ARENA;
      break;

    default:
      assert(false);
  }
}

void Stage::configureCurrentCamera(sf::RenderWindow &window) {
  switch (m_currentPlace) {
    case ARENA:
      m_arenaCamera.configure(window);
      break;

    case SAFE_ROOM:
      m_shopCamera.configure(window);
      break;

    default:
      assert(false);
  }
}

game::EventStatus Stage::onCharacterLocationEvent(game::EventType type, game::Event *event) {
  auto locationEvent = static_cast<CharacterLocationEvent *>(event);

  m_arenaCamera.setCenter({locationEvent->pos.x * BOX2D_PIXELS_PER_METER, locationEvent->pos.y * BOX2D_PIXELS_PER_METER});

  return game::EventStatus::KEEP;
}

game::EventStatus Stage::onEndWaveEvent(game::EventType type, game::Event *event) {
  togglePlace();

  return game::EventStatus::KEEP;
}

void Stage::update(const float dt) {
  switch (m_currentPlace) {
    case ARENA:
      m_enemies.update(dt);
      m_notifs.update(dt);
      break;

    case SAFE_ROOM:
      break;

    default:
      assert(false);
  }
}

void Stage::render(sf::RenderWindow& window) {
  switch (m_currentPlace) {
    case ARENA:
      m_arena.render(window);
      m_enemies.render(window);
      m_notifs.render(window);
      break;

    case SAFE_ROOM:
      m_shop.render(window);
      break;

    default:
      assert(false);
  }
}
