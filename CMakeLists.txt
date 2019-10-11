cmake_minimum_required(VERSION 3.15)
project(demmio)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(demmio main.cpp Style.cpp Style.h Util.cpp Util.h Slide.cpp Slide.h)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
    
    target_link_libraries(demmio jengine ${GLFW_LIBRARIES} pthread GL rt Xrandr Xxf86vm Xi
            Xinerama X11 dl SOIL freetype openal jjson)
    target_include_directories(demmio PUBLIC ${GLFW_INCLUDE_DIRS} /usr/local/include/freetype2)
    target_compile_options(demmio PUBLIC ${GLFW_CFLAGS_OTHER})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(GL OpenGL)
    find_library(CC Cocoa)
    find_library(IO IOKit)
    find_library(CV CoreVideo)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    target_link_directories(demmio PUBLIC /usr/local/lib)
    target_include_directories(demmio PUBLIC ${GLFW_INCLUDE_DIRS} /usr/local/include/freetype2)
    target_link_libraries(demmio ${GL} ${GLFW_LIBRARIES} SOIL openal freetype jengine jjson ${CC} ${IO} ${CV})
    target_compile_options(demmio PUBLIC ${GLFW_CFLAGS_OTHER})
endif()