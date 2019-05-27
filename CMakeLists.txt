cmake_minimum_required(VERSION 3.12)
project(ProjectLiver)

set(CMAKE_CXX_STANDARD 14)

include_directories(./libgraphics)
include_directories(./simpleGUI)
include_directories(./single_src/controller)
include_directories(./single_src/view)
include_directories(./single_src/model)
include_directories(./Linked_List)

aux_source_directory(./libgraphics LIB)
aux_source_directory(./simpleGUI GUI)
aux_source_directory(./single_src/model MODEL)
aux_source_directory(./single_src/view VIEW)
aux_source_directory(./single_src/controller CONTROLLER)
aux_source_directory(./Linked_List LINKED_LIST)
#
#SET(GCC_COVERAGE_COMPILE_FLAGS "-mwindows")
#SET(GCC_COVERAGE_LINK_FLAGS    "-mwindows")
#
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


add_executable(launcher WIN32 ${LIB} ${GUI} ${LINKED_LIST} launcher/launcher_main.c)
add_executable(single_main WIN32 ${LIB} ${MODEL} ${VIEW} ${CONTROLLER} single_src/single_main.c)