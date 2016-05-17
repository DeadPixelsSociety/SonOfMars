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
#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <game/WindowGeometry.h>

#include <vector>
#include <string>

#include "Game.h"

#define NOTIF_POINT     1
#define NOTIF_ALERT     2
#define NOTIF_ENNEMI_HAUT_GAUCHE  3
#define NOTIF_ENNEMI_HAUT_DROIT   4
#define NOTIF_ENNEMI_BAS_GAUCHE   5
#define NOTIF_ENNEMI_BAS_DROIT    6

struct Notification {
  sf::Uint8 type;
  sf::Vector2f pos;
  std::string text;
  float duration;
  float curTime;
};

class NotificationManager: public game::Entity {
public:
  NotificationManager(game::EventManager& events, game::ResourceManager& resource, game::WindowGeometry& geometry);
  virtual ~NotificationManager();
  virtual void update(const float dt) override;
  virtual void render(sf::RenderWindow& window) override;
  //game::EventStatus onCharacterStatsEvent(game::EventType type, game::Event *event);
  //void switchDisplay();

  bool addNotification(std::string name, sf::Uint8 type, sf::Vector2f pos, std::string text, float duration);
  bool removeNotification(std::string name);
  // Versions spéciales
  bool addEnnemiNotif(int nbEnnemies, sf::Uint8 coin);
private:
  game::WindowGeometry &m_geometry;
  game::EventManager& m_events;

  std::map<std::string, Notification> m_notifs;
  sf::Font *m_font;
};
#endif //NOTIFICATION_MANAGER_H
