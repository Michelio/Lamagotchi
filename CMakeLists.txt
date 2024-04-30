cmake_minimum_required(VERSION 3.27)
project(
  Lamagotchi
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)
find_package(Boost 1.83.0 REQUIRED)

add_subdirectory(src)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
