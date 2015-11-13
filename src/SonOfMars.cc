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

#include <game/Action.h>
#include <game/Camera.h>
#include <game/Clock.h>
#include <game/EntityManager.h>
#include <game/Log.h>
#include <game/WindowGeometry.h>
#include <game/WindowSettings.h>

#include "local/Arena.h"
#include "local/Enemy.h"
#include "local/EnemyManager.h"
#include "local/Character.h"
#include "local/config.h"
#include "local/ContactListener.h"
#include "local/Hub.h"
#include "local/SFMLDebugDraw.h"


int main(void) {
  game::Log::setLevel(game::Log::DEBUG);

  // initialize
  //static constexpr unsigned INITIAL_WIDTH = 800;
  //static constexpr unsigned INITIAL_HEIGHT = 600;

  game::WindowSettings settings(AREA_WIDTH, AREA_HEIGHT, "Son of Mars");
  game::WindowGeometry geometry(AREA_WIDTH, AREA_HEIGHT);

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);

  // add cameras
  game::CameraManager cameras;

  game::FixedRatioCamera mainCamera(AREA_WIDTH, AREA_HEIGHT, {AREA_WIDTH * 0.5f, AREA_HEIGHT * 0.5f});
  cameras.addCamera(mainCamera);

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);

  game::Action moveUP("Move UP");
  moveUP.addKeyControl(sf::Keyboard::Z);
  moveUP.setContinuous();
  actions.addAction(moveUP);

  game::Action moveDown("Move Down");
  moveDown.addKeyControl(sf::Keyboard::S);
  moveDown.setContinuous();
  actions.addAction(moveDown);

  game::Action moveLeft("Move Left");
  moveLeft.addKeyControl(sf::Keyboard::Q);
  moveLeft.setContinuous();
  actions.addAction(moveLeft);

  game::Action moveRight("Move Right");
  moveRight.addKeyControl(sf::Keyboard::D);
  moveRight.setContinuous();
  actions.addAction(moveRight);

  // Setup Box2d engine
  b2World b2_world(b2Vec2(0.0f, 0.0f));
  ContactListener contactListener;
  b2_world.SetContactListener(&contactListener);

  // Debug Box2D
  SFMLDebugDraw debugDraw(window);
  b2_world.SetDebugDraw(&debugDraw);
  debugDraw.SetFlags(b2Draw::e_shapeBit);

  // Events manager
  game::EventManager events;
  //add Resource manager
  game::ResourceManager resources;
  resources.addSearchDir("../share/");

  game::EntityManager mainEntities;

  Character character(b2_world, events);
  mainEntities.addEntity(character);

  Arena arena(b2_world, events);
  mainEntities.addEntity(arena);

  EnemyManager enemies(b2_world, events);
  mainEntities.addEntity(enemies);

  Hub hub(events,resources);
  mainEntities.addEntity(hub);

  // main loop
  game::Clock clock;

  while (window.isOpen()) {
    // input
    sf::Event event;

    while (window.pollEvent(event)) {
      actions.update(event);
      cameras.update(event);
      geometry.update(event);
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      settings.toggleFullscreen();
      settings.applyTo(window);
      auto sz = window.getSize();

      // fake resize event (not sent when going fullscreen before SFML 2.3.1)
      sf::Event event;
      event.type = sf::Event::Resized;
      event.size.width = sz.x;
      event.size.height = sz.y;
      cameras.update(event);
      geometry.update(event);
    }

    // Check move of character
    if (moveUP.isActive()) {
      character.move(Character::Direction::UP);
    }
    if (moveDown.isActive()) {
      character.move(Character::Direction::DOWN);
    }
    if (moveLeft.isActive()) {
      character.move(Character::Direction::LEFT);
    }
    if (moveRight.isActive()) {
      character.move(Character::Direction::RIGHT);
    }

    character.setTarget( window.mapPixelToCoords(
      sf::Mouse::getPosition(window)
      , mainCamera.getView()
    ) );

    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();
    mainEntities.update(dt);
    b2_world.Step(dt, 8, 3);

    // render
    window.clear(sf::Color::White);

    mainCamera.configure(window);
    mainEntities.render(window);
    b2_world.DrawDebugData();

    window.display();

    actions.reset();
  }

  return 0;
}

