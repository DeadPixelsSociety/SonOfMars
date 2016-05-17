#include "NotificationManager.h"

#include <iostream>

NotificationManager::NotificationManager(game::EventManager& events, game::ResourceManager& resources, game::WindowGeometry& geometry)
: m_geometry(geometry)
, m_events(events)
, m_font(nullptr)
{
  m_font=resources.getFont("GRECOromanLubedWrestling.ttf");
  assert(m_font!=nullptr);

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
    
    Notification& cn = it->second;

    sf::Text text;
    text.setFont(*m_font);
    text.setCharacterSize(30.0f);
    text.setString(cn.text);
    sf::FloatRect txtBounds = text.getGlobalBounds();

    switch (cn.type) {
      case NOTIF_POINT: {
        sf::RectangleShape rect(sf::Vector2f(txtBounds.width+20.0f, text.getGlobalBounds().height+20.0f));
        rect.setFillColor(sf::Color(100, 100, 100));
        rect.setPosition(cn.pos);
        text.setPosition(sf::Vector2f(-txtBounds.left, -txtBounds.top));
        text.setPosition(sf::Vector2f(-txtBounds.left, -txtBounds.top));
        text.move(cn.pos);
        text.move(10.0f, 10.0f);
        //circ.setSize({m_geometry.getXFromRight(0),m_geometry.getYRatio(0.05f,0.0f)});
        //circ.setRadius(100.0f);
        window.draw(rect);
        window.draw(text);

        } break;
      case NOTIF_ENNEMI_HAUT_DROIT: {
        float boxX = m_geometry.getXFromRight(txtBounds.width + 30.0f);
        sf::RectangleShape rect(sf::Vector2f(txtBounds.width+20.0f, text.getGlobalBounds().height+20.0f));
        rect.setFillColor(sf::Color(250, 0, 0));
        rect.setPosition(boxX-cn.pos.x, cn.pos.y);
        text.setPosition(sf::Vector2f(boxX-txtBounds.left, -txtBounds.top));
        text.move(0.0f, 20.0f);
        //text.move(cn.pos);
        
        window.draw(rect);
        window.draw(text);

      } break;
      case NOTIF_ENNEMI_HAUT_GAUCHE: {
        float boxX = 10.0f;
        sf::RectangleShape rect(sf::Vector2f(txtBounds.width+20.0f, text.getGlobalBounds().height+20.0f));
        rect.setFillColor(sf::Color(250, 0, 0));
        rect.setPosition(boxX+cn.pos.x, cn.pos.y);
        text.setPosition(sf::Vector2f(boxX-txtBounds.left, -txtBounds.top));
        text.move(10.0f, 10.0f);
        text.move(cn.pos);
        
        window.draw(rect);
        window.draw(text);

      } break;
      case NOTIF_ENNEMI_BAS_DROIT: {
        float boxX = m_geometry.getXFromRight(txtBounds.width + 30.0f),
              boxY = m_geometry.getYFromBottom(txtBounds.height + 30.0f);
        sf::RectangleShape rect(sf::Vector2f(txtBounds.width+20.0f, text.getGlobalBounds().height+20.0f));
        rect.setFillColor(sf::Color(250, 0, 0));
        rect.setPosition(boxX-cn.pos.x, boxY-cn.pos.y);
        //text.setPosition(sf::Vector2f(boxX-txtBounds.left, boxX-txtBounds.top));
        text.setPosition(rect.getPosition());
        text.move(10.0f, 0.0f);
        //text.move(cn.pos);
        
        window.draw(rect);
        window.draw(text);

      } break;
      case NOTIF_ENNEMI_BAS_GAUCHE: {
        float boxY = m_geometry.getYFromBottom(txtBounds.height + 30.0f);
        sf::RectangleShape rect(sf::Vector2f(txtBounds.width+20.0f, text.getGlobalBounds().height+20.0f));
        rect.setFillColor(sf::Color(250, 0, 0));
        rect.setPosition(cn.pos.x, boxY-cn.pos.y);
        text.setPosition(sf::Vector2f(-txtBounds.left, boxY-txtBounds.top));
        text.move(10.0f, -10.0f);
        text.move(cn.pos);
        
        window.draw(rect);
        window.draw(text);

      } break;
    }
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

bool NotificationManager::addEnnemiNotif(int nbEnnemies, sf::Uint8 coin) {
  return addNotification("ennemis", coin, sf::Vector2f(10.0f, 10.0f), "Ennemis !", 2.0f);
}
