cmake_minimum_required(VERSION 3.12)
project(ProjectLiver)

set(CMAKE_CXX_STANDARD 14)

include_directories(./libgraphics)
include_directories(./simpleGUI)
include_directories(single_src/controller)
include_directories(single_src/view)
include_directories(single_src/model)

aux_source_directory(./libgraphics LIB)
aux_source_directory(./simpleGUI GUI)
aux_source_directory(single_src/model MODEL)
aux_source_directory(single_src/view VIEW)
aux_source_directory(single_src/controller CONTROLLER)


add_executable(launcher ${LIB} ${GUI} ${MODEL} ${VIEW} ${CONTROLLER} single_src/single_main.c)
add_executable(single_main ${LIB} ${GUI} ${MODEL} ${VIEW} ${CONTROLLER} single_src/single_main.c)