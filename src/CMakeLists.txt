cmake_minimum_required(VERSION 2.8)

project("Son of Mars" CXX)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../modules")

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)
find_package(Box2D REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_definitions(-Wall -g -O2 -std=c++11)

add_executable(son-of-mars
    local/Assets.cc
    local/Character.cc
    local/Entity.cc
    local/Group.cc
    local/Random.cc
    local/Resources.cc
	local/SFMLDebugDraw.cc
	son-of-mars.cc
)

target_link_libraries(son-of-mars
	${SFML2_LIBRARIES}
	${BOX2D_LIBRARIES}
	${Boost_LIBRARIES}
)
