cmake_minimum_required(VERSION 3.12)
project(ProjectLiver)

set(CMAKE_CXX_STANDARD 14)

include_directories(./libgraphics)
include_directories(./simpleGUI)
include_directories(./src/controller)
include_directories(./src/view)
include_directories(./src/model)

aux_source_directory(./libgraphics LIB)
aux_source_directory(./simpleGUI GUI)
#aux_source_directory(./src SRC)
aux_source_directory(src/model MODEL)
aux_source_directory(src/view VIEW)
aux_source_directory(src/controller CONTROLLER)


add_executable(ProjectLiver
        ${LIB}
        ./libgraphics/exception.h ./libgraphics/extgraph.h ./libgraphics/gcalloc.h
        ${GUI}
        ${MODEL}
        ${VIEW}
        ${CONTROLLER}
#        src/view/drawers.h src/controller/handlers.h src/model/model.c src/model/model.h
        src/main.c src/model/consts.c)
