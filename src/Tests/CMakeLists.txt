cmake_minimum_required(VERSION 3.16)
#project(MultiplyTest LANGUAGES CXX)
project(MultiplyTest VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT6_DIR}/lib/cmake")
set(CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

#find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets)
include_directories(${GTEST_INCLUDE_DIR})
#include_directories(${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Qt6Gui_INCLUDE_DIRS}) #special variable got from find_package() to include QtWidgets dependencies directories


add_library(Parser ../Models/src/Parser/ParseObject.cc)
target_include_directories(Parser PUBLIC include/Parser)

#добавить googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(testUni school21_unitTest.cc)
target_link_libraries(testUni
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Core
        GTest::GTest
        Parser)
target_link_libraries(testUni PRIVATE Qt6::Gui)

add_test(testGUni testUni)

#add_subdirectory(src)
#add_subdirectory(tests)