cmake_minimum_required(VERSION 3.5)

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
)

set( LIBS
  -lncurses
)

add_executable(${PROJECT_NAME}  ${GAME_SOURCES})

target_link_libraries( ${PROJECT_NAME} ${LIBS} m )

