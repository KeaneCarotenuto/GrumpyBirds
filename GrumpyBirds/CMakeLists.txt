cmake_minimum_required(VERSION 3.0.0)
project(GrumpyBirds VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
FILE(GLOB SOURCES *.cpp)
add_executable(GrumpyBirds ${SOURCES})
LINK_DIRECTORIES(usr/lib)
find_package(SFML COMPONENTS system graphics window)
find_package(box2d)

TARGET_LINK_LIBRARIES(GrumpyBirds sfml-system sfml-graphics sfml-window box2d)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)