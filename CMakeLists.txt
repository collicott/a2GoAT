cmake_minimum_required (VERSION 2.6)
project(a2GoAT)

# check for in-source build, forbid it!
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR AND NOT MSVC_IDE)
  message(FATAL_ERROR "\nIn-source build attempt detected!\n"
    "Please create a new directory (e.g. build) and run `cmake ..`.\n"
    "Also don't forget to delete the created CMakeCache.txt and CMakeFiles dir"
    )
endif()
    
include(cmake/settings.cmake)
include(cmake/doxygen.cmake)

message(STATUS "*** Build Type:      " ${CMAKE_BUILD_TYPE})
message(STATUS "*** Compiler Flags:  " ${DEFAULT_COMPILE_FLAGS})
message(STATUS "*** Install libs to: " ${LIBRARY_OUTPUT_PATH})
message(STATUS "*** Install bin to:  " ${EXECUTABLE_OUTPUT_PATH})

# require a fairly recent ROOT version
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(ROOT "5.30" REQUIRED)

# since all subprojects need ROOT, set that up here
include_directories(${ROOT_INCLUDES})
link_directories(${ROOT_LIBRARY_DIR})

include_directories(inc)

add_executable(goat
   src/GoAT.cc 
   src/GSort.cc
   src/GParticleReconstruction.cc
   src/GoATTreeManager.cc
   src/GAcquTreeManager.cc
   )
target_link_libraries(goat ${ROOT_LIBRARIES})

add_executable(pi0
   src/PPi0.cc
   src/PPhysics.cc
   src/GoATTreeManager.cc
   src/GAcquTreeManager.cc
   )
target_link_libraries(pi0 ${ROOT_LIBRARIES})

add_executable(eta
   src/PEta.cc
   src/PPhysics.cc
   src/GoATTreeManager.cc
   src/GAcquTreeManager.cc
   )
target_link_libraries(eta ${ROOT_LIBRARIES})
