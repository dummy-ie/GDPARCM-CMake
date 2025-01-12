cmake_minimum_required(VERSION 3.28)
project(GDPARCM-Cmake LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED=ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
    GDPARCM 
    "src/Main.cpp" 
    "src/Controller/Application.cpp"
    "src/Controller/Singleton/GameObjectManager.cpp"  
    "src/Utility/FileUtility.h"
    "src/Model/FPSCounter.h"
 "src/Model/FPSCounter.cpp" "src/Config/Settings.h")

target_link_libraries(GDPARCM PRIVATE SFML::Graphics)
