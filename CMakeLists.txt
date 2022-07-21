cmake_minimum_required (VERSION 3.5.1)
project (waveformgen)
add_executable(waveformgen main.cpp classes/Tile.cpp classes/Cell.cpp classes/WaveFunctionCollapse.cpp)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library (GD gd)
find_library (PNG png)
find_library (M m)

find_path (GD_INCLUDE_DIR gd.h)

if(GD)
    message(STATUS "Found libGD: " ${GD})
endif(GD)

if(NOT GD)
    message(SEND_ERROR "Cannot find libGD")
    set(HAS_ERROR true)
endif(NOT GD)


if(NOT HAS_ERROR)
    include_directories(
        ${GD_INCLUDE_DIR}
    )

    target_link_libraries(waveformgen ${GD} ${PNG})
endif(NOT HAS_ERROR)

install (TARGETS waveformgen RUNTIME DESTINATION bin)