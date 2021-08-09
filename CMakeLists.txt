cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)

project(nvaders)


set( GAME_SOURCES
  main.cpp 
  timehelper.h
  src/EnemyCruiser.cpp       
  src/PlayerMissle.cpp
  src/EnemyDestroyer.cpp  
  src/PlayerShip.cpp
  src/EnemyMissle.cpp        
  src/Projectile.cpp
  src/EnemyShip.cpp       
  src/GameObject.cpp      
  src/Ship.cpp
  src/GameRunner.cpp
  src/MenuLevel.cpp
  src/Level.cpp
  src/GameLevel.cpp
  src/GameWonLevel.cpp
  src/GameLostLevel.cpp
)

set( LIBS
  -lncurses
)

add_executable(${PROJECT_NAME}  ${GAME_SOURCES})

target_link_libraries( ${PROJECT_NAME} ${LIBS} m )

