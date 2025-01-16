cmake_minimum_required(VERSION 3.26)
project(Main)

set(CMAKE_CXX_STANDARD 14)

add_executable(Main
    Source/Include/Global.hpp
    Source/Main.cpp

    Source/Include/Resources.hpp
    Source/Resources.cpp

    Source/Include/Engine.hpp
    Source/Engine.cpp

    Source/Include/UI.hpp
    Source/UI.cpp

    Source/Include/Utils.hpp
    Source/Utils.cpp

    Source/Include/Level.hpp
    Source/Level.cpp

    Source/Include/Player.hpp
    Source/Player.cpp

    Source/Include/Raycaster.hpp
    Source/Raycaster.cpp
)

include_directories(/usr/local/include)

find_package(SFML REQUIRED COMPONENTS system window graphics network audio)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Please install SFML and ensure CMake can find it.")
endif()

include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
