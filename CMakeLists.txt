# Setup the project
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(HPGe_simulation)


#Find Geant4 package, activating all available UI and Vis drivers by default
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
find_package(Geant4 REQUIRED ui_all vis_all)

#To add ROOT package to the project
set(ROOT_DIR /home/jkuroda/miniconda3/envs/root_env)
find_package(ROOT REQUIRED PATHS ${ROOT_DIR}/lib/cmake/ROOT)

#Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

#Locate sources and headers for this project
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#Include ROOT headers
include_directories(${ROOT_INCLUDE_DIRS})

# Add the executable, and link it to the Geant4 libraries
add_executable(HPGe_simulation HPGe_simulation.cc ${sources} ${headers})
target_link_libraries(HPGe_simulation ${Geant4_LIBRARIES} )

# Link ROOT libraries to your target
target_link_libraries(HPGe_simulation ${ROOT_LIBRARIES})

# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX

install(TARGETS HPGe_simulation DESTINATION bin)
