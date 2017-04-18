cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/includes)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB_RECURSE SOURCES "src/main/cpp/*.cpp")
message("Sources: " ${SOURCES})
add_library(game-engine SHARED ${SOURCES})

find_library(
        android-lib
        android
        atomic-lib
        atomic
        log-lib
        log
        glesv2-lib
        GLESv2
        opensles-lib
        OpenSLES
)

target_link_libraries(
        game-engine
        ${atomic-lib}
        ${log-lib}
        ${android-lib}
        GLESv2
        OpenSLES
)
