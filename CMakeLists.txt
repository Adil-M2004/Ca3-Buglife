cmake_minimum_required(VERSION 3.21)
project(bugs_life_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(bugs_life_project
        main.cpp
        Bug.cpp
        Crawler.cpp
        Hopper.cpp
        Board.cpp
        BugsLifeGUI.cpp
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.2/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network REQUIRED)

include_directories(C:/SFML-2.6.2/include)
target_link_libraries(bugs_life_project sfml-system sfml-window sfml-graphics)

# Copy resource files to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bugs.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/crawler-bugs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
