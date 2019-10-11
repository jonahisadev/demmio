cmake_minimum_required(VERSION 3.10)
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

install(TARGETS demmio RUNTIME DESTINATION /usr/bin)