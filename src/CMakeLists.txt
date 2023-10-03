cmake_minimum_required(VERSION 3.16)

project(3dViewer VERSION 1.0.0 LANGUAGES CXX C)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets LinguistTools Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#set(CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT5_DIR}/lib/cmake")
set(CMAKE_AUTOUIC_SEARCH_PATHS ./Views/Ui)
#find_package(OpenGL REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS OpenGL)
#find_package(Qt6  REQUIRED COMPONENTS OpenGLWidgets)
#find_package(Qt6 REQUIRED COMPONENTS Gui)
#set(CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
add_subdirectory(include/soil)
#include_directories("./include/QtGifImage/src/gifimage" "./include/QtGifImage/src/3rdParty/giflib")
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QtGifImage/src/gifimage
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QtGifImage/src/3rdParty/giflib
)

#file(GLOB_RECURSE ENGINE_HEADER

file(GLOB PROJECT_SOURCES
        Controlers/src/*.cc
        Models/src/Parser/*.cc
        Models/src/Buffers/*.cc
        Models/src/Point/*.cc
        Models/src/Media/*.cc
        Models/src/Object/*.cc
        Models/src/Shader/*.cc
        Models/src/Texture/*.cc
        Models/src/Transformation/*.cc
        Models/src/Camera/*.cc
        Views/src/Camera/*.cc
        Views/src/Color/*.cc
        Views/src/Light/*.cc
        Views/src/MainWindow/*.cc
        Views/src/Transformation/*.cc
        Views/src/Texture/*.cc
        Views/src/Draw/*.cc
        main.cc
        Controlers/include/*.h
        Models/include/Camera/*.h
        Models/include/Buffers/*.h
        Models/include/Media/*.h
        Models/include/Object/*.h
        Models/include/Shader/*.h
        Models/include/Texture/*.h
        Models/include/Transformation/*.h
        Models/include/Parser/*.h
        Models/include/Point/*.h
        Views/include/Camera/*.h
        Views/include/Color/*.h
        Views/include/Light/*.h
        Views/include/MainWindow/*.h
        Views/include/Transformation/*.h
        Views/include/Texture/*.h
        Views/include/Draw/*.h
        Settings/*.h
        Views/Ui/*.ui
        ResourceFiles/*.qrc


        ./include/QtGifImage/src/gifimage/qgifimage.h
        ./include/QtGifImage/src/gifimage/qgifimage.cpp
        ./include/QtGifImage/src/gifimage/qgifglobal.h
        ./include/QtGifImage/src/gifimage/qgifimage_p.h

        ./include/QtGifImage/src/3rdParty/giflib/gif_lib.h
        ./include/QtGifImage/src/3rdParty/giflib/gif_hash.h
        ./include/QtGifImage/src/3rdParty/giflib/gif_lib_private.h

        ./include/QtGifImage/src/3rdParty/giflib/dgif_lib.c
        ./include/QtGifImage/src/3rdParty/giflib/egif_lib.c
        ./include/QtGifImage/src/3rdParty/giflib/gifalloc.c
        ./include/QtGifImage/src/3rdParty/giflib/gif_err.c
        ./include/QtGifImage/src/3rdParty/giflib/gif_font.c
        ./include/QtGifImage/src/3rdParty/giflib/gif_hash.c
        ./include/QtGifImage/src/3rdParty/giflib/quantize.c

        ${TS_FILES}

        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(3dViewer
                MANUAL_FINALIZATION
                ${PROJECT_SOURCES}
                )

        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#add_executable(3dViewer ${PROJECT_SOURCES})
endif()

#target_include_directories(3dViewer PRIVATE src)
target_include_directories(3dViewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(3dViewer PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

#target_link_libraries(3dViewer
#        Qt5::Core
#        Qt5::Gui
#        Qt5::Widgets
#        Qt5::OpenGL
#        Qt5::OpenGLWidgets
#        ${OPENGL_LIBRARIES}
#    )

target_link_libraries(3dViewer PRIVATE Qt6::OpenGL)
target_link_libraries(3dViewer PRIVATE Qt6::Gui)
target_link_libraries(3dViewer PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(3dViewer PRIVATE Qt6::Core)
target_link_libraries(3dViewer PRIVATE SOIL)

# target_link_libraries(${PROJECT_NAME} PRIVATE qtgif)
#set_source_files_properties(ResourceFiles/res.qrc PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(calc)
# endif()


add_compile_options("-Wall -Wextra -Wpedantic -Werror")
