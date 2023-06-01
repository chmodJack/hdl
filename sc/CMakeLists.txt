cmake_minimum_required(VERSION 3.12)
enable_testing()
project(main)
find_package(SVC REQUIRED)
set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cpp)

svc_target(main INIT_LOCAL_VARS ELAB_TOP top)
