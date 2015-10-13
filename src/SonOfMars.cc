/*
 * Copyright (c) 2015 OFNI
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
#include "local/Character.h"
#include "local/config.h"
#include "local/EnemyManager.h"
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

  // Debug Box2D
  SFMLDebugDraw debugDraw(window);
  b2_world.SetDebugDraw(&debugDraw);
  debugDraw.SetFlags(b2Draw::e_shapeBit);

  // Events manager 
  game::EventManager events;

  game::EntityManager mainEntities;

  Character character(b2_world);
  mainEntities.addEntity(character);
  
  Enemy enemy(b2_world, b2Vec2(0,0), character);
  mainEntities.addEntity(enemy);

  Arena arena(b2_world, events);
  mainEntities.addEntity(arena);

  EnemyManager enemies(events);
  mainEntities.addEntity(enemies);

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

