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
, m_rand()
, m_muted(false)
, m_mainVolume(100.0f)
{
  // Load resources
  initSound("hit_enemy", "sounds/hit_enemy_metallic.wav");
  initSound("hit_player", "sounds/hit_player_1.wav");
  initSound("player_die_1", "sounds/player_death_1.wav", 50.0f);
  initSound("player_die_2", "sounds/player_death_2.wav");
  initSound("enemy_die_1", "sounds/enemy_death_1.wav");
  initSound("player_walk", "sounds/player_walk.wav", 25.0f, true);

  // Register events
  events.registerHandler<CharacterHitEnemyEvent>(&SoundManager::onCharacterHitEnemy, this);
  events.registerHandler<EnemyHitCharacterEvent>(&SoundManager::onEnemyHitCharacter, this);
  events.registerHandler<CharacterDeathEvent>(&SoundManager::onCharacterDie, this);
  events.registerHandler<EnemyDeathEvent>(&SoundManager::onEnemyDie, this);
  events.registerHandler<CharacterMovementEvent>(&SoundManager::onCharacterMove, this);

}

// Tools

bool SoundManager::initSound(std::string name, const boost::filesystem::path& path, float volume, bool loop) {
  bool alreadyExists = true;
  if (m_sounds.find(name) == m_sounds.end() ) {
    alreadyExists = false;
    auto buffer = m_res.getSoundBuffer(path);
    if (buffer == nullptr) {
      std::cout << "Unable to find " << path << std::endl;
      return false;
    } else {
      sf::Sound newSound;
      newSound.setBuffer(*buffer);
      newSound.setLoop(loop);
      newSound.setVolume(volume);
      m_sounds.insert(std::pair<std::string, sf::Sound>(name, newSound));
    }
  }

  setVol(name, volume);
  
  return alreadyExists;
}

float SoundManager::setVol(std::string name, float newVolume) {
  float finalVolume, oldVolume;

  if (m_sounds.find(name) == m_sounds.end()) {
    return -1.0f;
  }

  oldVolume = m_volumes[name];
  m_volumes[name] = newVolume;
  finalVolume = m_volumes[name] * m_mainVolume / 100.0f;

  if (m_muted)
    m_sounds[name].setVolume(0.0f);
  else
    m_sounds[name].setVolume(finalVolume);
  return oldVolume;
}


bool SoundManager::play(std::string name) {
  auto it = m_sounds.find(name);
  if (it == m_sounds.end() || it->second.getStatus() == sf::SoundSource::Status::Playing) {
    return false;
  }
  it->second.play();
  return true;
}

bool SoundManager::replay(std::string name) {
  auto it = m_sounds.find(name);
  if (it == m_sounds.end()) {
    return false;
  }
  it->second.play();
  return true;
}

bool SoundManager::playRandom(SoundList list) {
  return play(list[ m_rand.computeUniformInteger(0, list.size()-1) ]);
}


bool SoundManager::stop(std::string name) {
  auto it = m_sounds.find(name);
  if (it == m_sounds.end()) {
    return false;
  }
  it->second.stop();
  return true;
}



void SoundManager::updateVolumes() {
  std::string name;
  for(std::map<std::string, sf::Sound>::iterator it = m_sounds.begin() ; it != m_sounds.end() ; it++) {
    name = it->first;
    if (m_volumes.find(name) != m_volumes.end()) {
      setVol(name, m_volumes[it->first]);
    }
  }
}

void SoundManager::setMainVolume(float newVol) {
  if (newVol >= 0.0f && newVol <= 100.0f)
    m_mainVolume = newVol;
}

void SoundManager::setMuted(bool muted) {
  if(m_muted != muted) {
    m_muted = muted;
    updateVolumes();
  }
}

void SoundManager::toggleSound() {
  setMuted(!m_muted);
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

game::EventStatus SoundManager::onEnemyHitCharacter(game::EventType type, game::Event *event) {
  auto hitEvent = static_cast<EnemyHitCharacterEvent *>(event);
  float addedVolume = hitEvent->damages*5.0f;
  
  if(addedVolume > 75.0f)
    setVol("hit_player", 100.0f);
  else
    setVol("hit_player", 25.0f + addedVolume);
    
  play("hit_player");
  
  return game::EventStatus::KEEP;
}

game::EventStatus SoundManager::onCharacterDie(game::EventType type, game::Event *event) {
  stop("player_walk"); // The Walking Dead *goes out*
  stop("hit_player");
  playRandom(SoundList({"player_die_1", "player_die_2"}));
  
  return game::EventStatus::KEEP;
}

game::EventStatus SoundManager::onEnemyDie(game::EventType type, game::Event *event) {
  play("enemy_die_1");
  
  return game::EventStatus::KEEP;
}

game::EventStatus SoundManager::onCharacterMove(game::EventType type, game::Event *event) {
  auto moveEvent = static_cast<CharacterMovementEvent *>(event);
  if(moveEvent->moves) {
    play("player_walk");
  } else {
    stop("player_walk");
  }
  
  return game::EventStatus::KEEP;
}
