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
    "src/Config/Settings.h" 
    "src/Utility/FileUtils.h"
    "src/Utility/StringUtils.h" 
    "src/Utility/LogUtils.h"
    "src/Controller/Application.cpp"
    "src/Controller/Singleton/GameObjectManager.cpp"  
    "src/Controller/Singleton/TextureManager.cpp"
    "src/GameObject/ScrollingBackground.cpp"
    "src/GameObject/FPSCounter.cpp" 
    "src/GameObject/TextureDisplay.cpp" 
    "src/GameObject/IconObject.cpp" 
    "src/Threading/IETThread.cpp"
    "src/Threading/IETThread.h"
    "src/Threading/IExecutionEvent.cpp"
    "src/Threading/IExecutionEvent.h"
    "src/Threading/StreamAssetLoader.cpp"
    "src/Threading/StreamAssetLoader.h"
    "src/Threading/ThreadPool.cpp"
    "src/Threading/ThreadPool.h"
    "src/Threading/PoolWorkerThread.cpp"
    "src/Threading/PoolWorkerThread.h"
    "src/Threading/IWorkerAction.cpp"
    "src/Threading/IWorkerAction.h"
)

target_link_libraries(GDPARCM PRIVATE SFML::Graphics)
