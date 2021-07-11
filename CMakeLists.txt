cmake_minimum_required(VERSION 3.0.0)
project(depth-pipeline VERSION 0.1.0)

include(CTest)

enable_testing()

find_package(realsense2 REQUIRED)

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_executable(depth-pipeline main.cpp)
target_link_libraries( depth-pipeline  ${OpenCV_LIBS} ${realsense2_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
