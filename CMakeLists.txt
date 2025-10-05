cmake_minimum_required(VERSION 3.10)
project(OS_Lab1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message("Build for Linux")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message("Build for Windows")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /WX /Zi")
endif ()

add_library(prime_lib src/prime.cpp)
target_include_directories(prime_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(os_lib src/linux_os.cpp)
target_include_directories(os_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(parent src/parent.cpp)
add_executable(child src/child.cpp)
target_link_libraries(child PRIVATE prime_lib)
target_link_libraries(parent PRIVATE os_lib)
target_link_libraries(child PRIVATE os_lib)