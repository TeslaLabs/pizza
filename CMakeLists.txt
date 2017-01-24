cmake_minimum_required(VERSION 3.2)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  add_definitions(-DDEBUG_MODE)
endif()

string(CONCAT ADDITIONAL_FLAGS
       "-Wall "
       "-std=c++11 "
       "-pedantic "
       "-fno-exceptions "
       "-fno-rtti"
       )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_FLAGS}")

list(APPEND DIR_TO_INCLUDE "${CMAKE_SOURCE_DIR}/include")
list(APPEND DIR_TO_LINK "${CMAKE_SOURCE_DIR}/lib")

add_definitions("-DGOOGLE_PROTOBUF_NO_RTTI")

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
    "args/args.cc"

    "engine/engine.cc"

    "event/eventdata.cc"
    "event/sdlevent.cc"

    "log/termlog.cc"

    "math/matrix.cc"
    "math/vec3.cc"
    "math/vec4.cc"

    "proto/data.pb.cc"

    "render/glrender.cc"
    "render/glrender_camera.cc"
    "render/glrender_mesh.cc"
    "render/glrender_shader.cc"
    "render/irender.cc"
    "render/model.cc"

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

if (APPLE)
  list(APPEND PIZZA_SOURCES
       "timer/appletimer.cc"
       )
elseif(UNIX)
  list(APPEND PIZZA_SOURCES
       "timer/linuxtimer.cc"
       )
  list(APPEND PIZZA_LIBS GL GLEW pthread m dl SDL2 SDL2main)
endif()

add_library(engine ${PIZZA_SOURCES})
target_link_libraries(engine ${PIZZA_LIBS})

add_executable(mcomp ${MCOMP_SOURCES})
target_link_libraries(mcomp ${MCOMP_LIBS})

add_executable(server "net/server.cc")
add_executable(client "net/client.cc")

if (APPLE)
  string(CONCAT FRAMEWORKS
         "-F ${CMAKE_SOURCE_DIR}/lib "
         "-framework SDL2 "
         "-framework OpenGL "
         )
  set_target_properties(engine PROPERTIES LINK_FLAGS ${FRAMEWORKS})
  set_target_properties(mcomp PROPERTIES LINK_FLAGS ${FRAMEWORKS})
endif()
