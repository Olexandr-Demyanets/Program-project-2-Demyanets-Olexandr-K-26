cmake_minimum_required(VERSION 3.16)
project(Project2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
set(OPT_LEVEL "-O3" CACHE STRING "Optimization level: -O0 or -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${OPT_LEVEL} -DNDEBUG" CACHE STRING "" FORCE)

find_package(Threads REQUIRED)

find_package(TBB CONFIG QUIET)

add_executable(generate generate_main.cpp sequence_io.cpp)
add_executable(benchmark main.cpp sequence_io.cpp adjacent_ops.cpp benchmark.cpp)

target_link_libraries(benchmark PRIVATE Threads::Threads)
target_compile_definitions(benchmark PRIVATE BUILD_OPT_LEVEL="${OPT_LEVEL}")

if(TBB_FOUND)
    target_link_libraries(benchmark PRIVATE TBB::tbb)
    message(STATUS "TBB found: execution policies will run in parallel")
else()
    message(WARNING "TBB not found: execution::par/par_unseq will run sequentially")
endif()

foreach(t generate benchmark)
    target_compile_options(${t} PRIVATE -Wall -Wextra)
endforeach()
