cmake_minimum_required(VERSION 3.10)
project(game)

find_library(SDL2_LIBRARY NAMES SDL2 REQUIRED)
find_library(SDL2_image_LIBRARY NAMES SDL2_image REQUIRED)
find_library(SDL2_ttf_LIBRARY NAMES SDL2_ttf REQUIRED)
find_library(SDL2_mixer_LIBRARY NAMES SDL2_mixer REQUIRED)

find_package(TIFF REQUIRED)

find_path(SDL2_INCLUDE_DIRS SDL2/SDL.h REQUIRED )
message( STATUS "SDL2_INCLUDE_DIRS [${SDL2_INCLUDE_DIRS}]" )
find_path(SDL2_image_INCLUDE_DIRS SDL2/SDL_image.h REQUIRED )
message( STATUS "SDL2_image_INCLUDE_DIRS [${SDL2_image_INCLUDE_DIRS}]" )
find_path(SDL2_ttf_INCLUDE_DIRS SDL2/SDL_ttf.h REQUIRED )
message( STATUS "SDL2_ttf_INCLUDE_DIRS [${SDL2_ttf_INCLUDE_DIRS}]" )
find_path(SDL2_mixer_INCLUDE_DIRS SDL2/SDL_mixer.h REQUIRED )
message( STATUS "SDL2_mixer_INCLUDE_DIRS [${SDL2_mixer_INCLUDE_DIRS}]" )

add_executable(game src/main.cpp src/implementations/Player.cpp src/implementations/Window.cpp src/implementations/Projectile.cpp src/implementations/Map.cpp src/implementations/Sprite.cpp src/implementations/GameObject.cpp)
target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS})
target_link_libraries(game ${TIFF_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_image_LIBRARY} ${SDL2_ttf_LIBRARY} ${SDL2_mixer_LIBRARY})
