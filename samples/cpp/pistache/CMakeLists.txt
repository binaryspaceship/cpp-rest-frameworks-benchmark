cmake_minimum_required(VERSION 3.5)
project(main)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_library(PISTACHE_LIB net_static)
find_package(Threads REQUIRED)
find_package(RapidJSON REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main
  ${CMAKE_THREAD_LIBS_INIT}
  ${PISTACHE_LIB}
)
target_compile_features(main PRIVATE cxx_range_for)