cmake_minimum_required(VERSION 2.8)

project("Son of Mars" CXX)

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../modules")

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)
find_package(Box2D REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/local/config.h.in ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/local/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

add_definitions(-Wall -g -O2 -std=c++11 -Wextra)
# add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(son-of-mars
  # Gameskel of Jube (https://github.com/jube/gameskel)
  # base
  game/AssetManager.cc
  game/Clock.cc
  game/EventManager.cc
  game/Log.cc
  game/Random.cc
  # graphics
  game/Action.cc
  game/Animation.cc
  game/Camera.cc
  game/Control.cc
  game/Entity.cc
  game/EntityManager.cc
  game/ResourceManager.cc
  game/WindowGeometry.cc
  game/WindowSettings.cc
  # model
  game/Model.cc
  game/ModelManager.cc

  # Own class
  local/Arena.cc
  local/Character.cc
  local/ContactListener.cc
  local/Enemy.cc
  local/EnemyManager.cc
  local/Hud.cc
  local/NotificationManager.cc
  local/SFMLDebugDraw.cc
  local/SoundManager.cc
  local/Stage.cc
  local/Target.cc
  SonOfMars.cc
)

target_link_libraries(son-of-mars
  ${SFML2_LIBRARIES}
  ${BOX2D_LIBRARIES}
  ${Boost_LIBRARIES}
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/share/son-of-mars"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)

install(
  TARGETS son-of-mars
  RUNTIME DESTINATION games
)
