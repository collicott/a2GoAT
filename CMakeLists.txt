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
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GCorrectScalers.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeManager.cc
   src/GTreeMeson.cc
   src/GCorrectScalers.cc
   src/GoAT.cc
   )
target_link_libraries(goat ${ROOT_LIBRARIES})

add_executable(meson
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GMesonReconstruction.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeManager.cc
   src/GTreeMeson.cc
   src/GMesonReconstruction.cc
   src/meson.cc
   )
target_link_libraries(meson ${ROOT_LIBRARIES})

add_executable(plotTagger
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GPlotTagger.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeManager.cc
   src/GTreeMeson.cc
   src/GPlotTagger.cc
   src/plotTagger.cc
   )
target_link_libraries(plotTagger ${ROOT_LIBRARIES})

add_executable(tagger
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GTaggerReconstruction.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeManager.cc
   src/GTreeMeson.cc
   src/GTaggerReconstruction.cc
   src/tagger.cc
   )
target_link_libraries(tagger ${ROOT_LIBRARIES})


