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

#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include <cmath>

#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <game/Random.h>

#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>

#include "Game.h"

typedef std::vector<std::string> SoundList;

class SoundManager {
public:
  SoundManager(game::EventManager& events, game::ResourceManager &resources);

  // Tools
  bool initSound(std::string name, const boost::filesystem::path& path, float volume = 25.0f, bool loop = false);
  float setVol(std::string name, float newVolume);

  bool play(std::string name);
  bool replay(std::string name);
  bool playRandom(SoundList list);
  bool stop(std::string name);

  void updateVolumes();
  void setMainVolume(float newVol);
  void setMuted(bool muted);
  void toggleSound();

  // Events handlers
  game::EventStatus onCharacterHitEnemy(game::EventType type, game::Event *event);
  game::EventStatus onEnemyHitCharacter(game::EventType type, game::Event *event);
  game::EventStatus onCharacterDie(game::EventType type, game::Event *event);
  game::EventStatus onEnemyDie(game::EventType type, game::Event *event);
  game::EventStatus onCharacterMove(game::EventType type, game::Event *event);

private:
  game::EventManager& m_events;
  game::ResourceManager& m_res;
  game::Random m_rand;

  std::map<std::string, sf::Sound> m_sounds;
  std::map<std::string, float> m_volumes;
  bool m_muted;
  float m_mainVolume;

};

#endif // SOUND_MANAGER_H
