cmake_minimum_required(VERSION 3.5)
project(main)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_library(RESTBED_LIB restbed)
find_package(Threads REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(OpenSSL 1.0.0 REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main
  ${CMAKE_THREAD_LIBS_INIT}
  ${RESTBED_LIB}
  OpenSSL::SSL
)
target_compile_features(main PRIVATE cxx_range_for)