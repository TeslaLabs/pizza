cmake_minimum_required(VERSION 3.2)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DDEBUG_MODE)
else()
    message("Not in debug mode")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic")

include_directories(
    "${CMAKE_SOURCE_DIR}/include"
    "/usr/local/Cellar/protobuf/3.1.0/include"
    )

link_directories(
    "${CMAKE_SOURCE_DIR}/lib"
    )

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

    "window/sdlwindow.cc"
    )
add_library(engine ${PIZZA_SOURCES})
target_link_libraries(engine protobuf)

set(MCOMP_SOURCES
    "mcomp/main.cc"
    "mcomp/mcomp.cc"
    )
add_executable(mcomp ${MCOMP_SOURCES})
target_link_libraries(mcomp engine)

set(EXAMPLE_SOURCES
    "example/main.cc"
    )
add_executable(example ${EXAMPLE_SOURCES})

if (APPLE)
    set_target_properties(engine PROPERTIES LINK_FLAGS
        "-F {$CMAKE_SOURCE_DIR}/lib -framework SDL2 -framework OpenGL")
    set_target_properties(mcomp PROPERTIES LINK_FLAGS
        "-F ${CMAKE_SOURCE_DIR}/lib -framework SDL2 -framework OpenGL")
    set_target_properties(example PROPERTIES LINK_FLAGS
        "-F ${CMAKE_SOURCE_DIR}/lib -framework SDL2 -framework OpenGL")
endif()
