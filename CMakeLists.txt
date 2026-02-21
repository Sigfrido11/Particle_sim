cmake_minimum_required(VERSION 3.16)
project(particle_simulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

add_executable(particle_sim
  main.cpp
  particle.cpp
  particletype.cpp
  resonancetype.cpp
)

target_include_directories(particle_sim PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(particle_sim PRIVATE ${ROOT_LIBRARIES})

# Useful for ROOT reflex/IO on some setups
add_definitions(${ROOT_CXX_FLAGS})
