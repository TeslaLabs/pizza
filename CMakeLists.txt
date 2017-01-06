cmake_minimum_required(VERSION 3.2)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DDEBUG_MODE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
list(APPEND DIR_TO_INCLUDE "${CMAKE_SOURCE_DIR}/include")
list(APPEND DIR_TO_LINK "${CMAKE_SOURCE_DIR}/lib")

if(APPLE)
    add_definitions("-D_THREAD_SAFE") # protobuf
    list(APPEND DIR_TO_INCLUDE "/usr/local/Cellar/protobuf/3.1.0/include")
elseif(UNIX)
    add_definitions("-D_REENTRANT") # sdl
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--enable-new-dtags -pthread")
    list(APPEND DIR_TO_LINK "/usr/local/lib")
    list(APPEND DIR_TO_INCLUDE "/usr/local/include")
endif()

include_directories(${DIR_TO_INCLUDE})
link_directories(${DIR_TO_LINK})

set(PIZZA_SOURCES
    "engine/engine.cc"

    "event/sdlevent.cc"

    "log/termlog.cc"

    "math/matrix.cc"
    "math/vec3.cc"
    "math/vec4.cc"

    "proto/data.pb.cc"

    "render/glrender.cc"
    "render/irender.cc"
    "render/model.cc"

    "timer/timer.cc"

    "window/sdlwindow.cc"
    )
set(PIZZA_LIBS
    protobuf
    )

set(MCOMP_SOURCES
    "mcomp/main.cc"
    "mcomp/mcomp.cc"
    )
set(MCOMP_LIBS engine)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c90 -pedantic")

if (APPLE)
elseif(UNIX)
    list(APPEND PIZZA_LIBS GL GLEW pthread m dl SDL2 SDL2main)
endif()

add_library(engine ${PIZZA_SOURCES})
target_link_libraries(engine ${PIZZA_LIBS})

add_executable(mcomp ${MCOMP_SOURCES})
target_link_libraries(mcomp ${MCOMP_LIBS})

if (APPLE)
    set_target_properties(engine PROPERTIES LINK_FLAGS
        "-F {$CMAKE_SOURCE_DIR}/lib -framework SDL2 -framework OpenGL")
    set_target_properties(mcomp PROPERTIES LINK_FLAGS
        "-F ${CMAKE_SOURCE_DIR}/lib -framework SDL2 -framework OpenGL")
endif()
