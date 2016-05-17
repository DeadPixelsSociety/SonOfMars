#include "NotificationManager.h"

#include <iostream>

NotificationManager::NotificationManager(game::EventManager& events, game::WindowGeometry& geometry)
: m_geometry(geometry)
, m_events(events)
{

}

NotificationManager::~NotificationManager() {

}

void NotificationManager::update(const float dt) {
  // for(std::map<std::string, Notification>::iterator it = m_notifs.begin() ; it != m_notifs.end() ; it++) {
  //   if(it->second.duration > 0.0f) {
  //     it->second.curTime += dt;
  //     if (it->second.curTime > it->second.duration)
  //       removeNotification(it->first);
  //   }
  // }
}

void NotificationManager::render(sf::RenderWindow& window) {
  for(std::map<std::string, Notification>::iterator it = m_notifs.begin() ; it != m_notifs.end() ; it++) {
    std::cout << "Notification " << it->first << std::endl;
    std::cout << "    PositionX: " << it->second.pos.x << std::endl;
    std::cout << "    PositionY: " << it->second.pos.y << std::endl;
    std::cout << "    Text: " << it->second.text << std::endl;
    std::cout << "    Duration: " << it->second.duration << std::endl;
    std::cout << "    Current time: " << it->second.curTime << std::endl;
  }
}

bool NotificationManager::addNotification(std::string name, sf::Uint8 type, sf::Vector2f pos, std::string text, float duration) {
  bool exists = m_notifs.find(name) != m_notifs.end();
  m_notifs[name].type = type;
  m_notifs[name].pos = pos;
  m_notifs[name].text = text;
  m_notifs[name].duration = duration;
  m_notifs[name].curTime = 0.0f;
  return exists;
}

bool NotificationManager::removeNotification(std::string name) {
  if (m_notifs.find(name) == m_notifs.end())
    return false;
  m_notifs.erase(name);
  return true;
}
