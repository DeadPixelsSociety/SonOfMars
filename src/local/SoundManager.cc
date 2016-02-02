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

#include "SoundManager.h"

SoundManager::SoundManager(game::EventManager& events, game::ResourceManager &resources)
: m_events(events)
, m_res(resources)
, m_muted(false)
{
  // Load resources
  // auto buffer = resources.getSoundBuffer("sounds/hit_enemy.wav");
  // m_hitEnemySound.setBuffer(*buffer);
  // m_hitEnemySound.setLoop(false);
  // m_hitEnemySound.setVolume(25.0f);
  initSound("hit_enemy", "sounds/hit_enemy.wav");
  initSound("player_die_1", "sounds/player_death_1.wav", 50.0f);
  initSound("player_die_2", "sounds/player_death_2.wav");
  

  // Register events
  events.registerHandler<CharacterHitEnemyEvent>(&SoundManager::onCharacterHitEnemy, this);
  events.registerHandler<CharacterDeathEvent>(&SoundManager::onCharacterDie, this);

}

// Tools

bool SoundManager::initSound(std::string name, const boost::filesystem::path& path, float volume, bool loop) {
  if (m_sounds.find(name) == m_sounds.end() ) {
    auto buffer = m_res.getSoundBuffer(path);
    if (buffer != nullptr) {
      sf::Sound newSound;
      newSound.setBuffer(*buffer);
      newSound.setLoop(loop);
      newSound.setVolume(volume);
      m_sounds.insert(std::pair<std::string, sf::Sound>(name, newSound));
    }
  }
  return false;
}

float SoundManager::setVol(std::string name, float newVolume) {
  float oldVolume;
  auto it = m_sounds.find(name);
  if (it == m_sounds.end()) {
    return -1;
  }

  oldVolume = it->second.getVolume();
  it->second.setVolume(newVolume);
  return oldVolume;
}


bool SoundManager::play(std::string name) {
  auto it = m_sounds.find(name);
  if (it == m_sounds.end() || it->second.getStatus() == sf::SoundSource::Status::Playing) {
    std::cout << "Unable to play " << name << std::endl;
    return false;
  }
  it->second.play();
  std::cout << "Playing " << name << std::endl;
  return true;
}

bool SoundManager::replay(std::string name) {
  auto it = m_sounds.find(name);
  if (it == m_sounds.end()) {
    std::cout << "Unable to play " << name << std::endl;
    return false;
  }
  it->second.play();
  std::cout << "Playing " << name << std::endl;
  return true;
}



// Events handlers

game::EventStatus SoundManager::onCharacterHitEnemy(game::EventType type, game::Event *event) {
  auto hitEvent = static_cast<CharacterHitEnemyEvent *>(event);
  float addedVolume = hitEvent->numberOfHits*5.0f;
  
  if(addedVolume > 75.0f)
    setVol("hit_enemy", 100.0f);
  else
    setVol("hit_enemy", 25.0f + addedVolume);
    
  replay("hit_enemy");
  
  return game::EventStatus::KEEP;
}

game::EventStatus SoundManager::onCharacterDie(game::EventType type, game::Event *event) {
  play("player_die_1");
  // play("player_die_2");
  
  return game::EventStatus::KEEP;
}
