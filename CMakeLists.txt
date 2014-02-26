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
   src/GTreeMeson.cc
   src/GTreeManager.cc
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
   src/GTreeMeson.cc
   src/GTreeManager.cc
   src/GMesonReconstruction.cc
   src/meson.cc
   )
target_link_libraries(meson ${ROOT_LIBRARIES})

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
   src/GTreeMeson.cc
   src/GTreeManager.cc
   src/GTaggerReconstruction.cc
   src/tagger.cc
   )
target_link_libraries(tagger ${ROOT_LIBRARIES})

add_executable(proton
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GProtonReconstruction.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeManager.cc
   src/GTreeMeson.cc
   src/GProtonReconstruction.cc
   src/proton.cc
   )
target_link_libraries(proton ${ROOT_LIBRARIES})


add_executable(plot
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GHistParticle.h
   inc/GHistTaggedParticle.h
   inc/GHistTaggedMeson.h
   inc/GPlot.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeMeson.cc
   src/GTreeManager.cc
   src/GHistParticle.cc
   src/GHistTaggedParticle.cc
   src/GHistTaggedMeson.cc
   src/GPlot.cc
   src/plot.cc
   )
target_link_libraries(plot ${ROOT_LIBRARIES})

add_executable(cut
   inc/GTree.h
   inc/GTreeRawEvent.h
   inc/GTreeEvent.h
   inc/GTreeTagger.h
   inc/GTreeScaler.h
   inc/GTreeParticle.h
   inc/GTreeMeson.h
   inc/GTreeManager.h
   inc/GHistParticle.h
   inc/GHistTaggedParticle.h
   inc/GHistTaggedMeson.h
   inc/GCut.h
   src/GTree.cc
   src/GTreeRawEvent.cc
   src/GTreeEvent.cc
   src/GTreeTagger.cc
   src/GTreeScaler.cc
   src/GTreeParticle.cc
   src/GTreeMeson.cc
   src/GTreeManager.cc
   src/GHistParticle.cc
   src/GHistTaggedParticle.cc
   src/GHistTaggedMeson.cc
   src/GCut.cc
   src/cut.cc
   )
target_link_libraries(cut ${ROOT_LIBRARIES})
