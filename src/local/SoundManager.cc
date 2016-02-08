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
    return -1.0f;
  }

  oldVolume = it->second.getVolume();
  it->second.setVolume(newVolume);
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
