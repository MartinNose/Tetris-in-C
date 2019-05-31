cmake_minimum_required(VERSION 3.12)
project(ProjectLiver)

set(CMAKE_CXX_STANDARD 14)

include_directories(./libgraphics)
include_directories(./simpleGUI)
include_directories(./single_src/controller)
include_directories(./single_src/view)
include_directories(./single_src/model)
include_directories(./Linked_List)
include_directories(./File_System)
include_directories(./Sound)

aux_source_directory(./libgraphics LIB)
aux_source_directory(./simpleGUI GUI)
aux_source_directory(./single_src/model MODEL)
aux_source_directory(./single_src/view VIEW)
aux_source_directory(./single_src/controller CONTROLLER)
aux_source_directory(./File_System FILE_SYS)
aux_source_directory(./Sound SOUND)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-mwindows")
#SET(GCC_COVERAGE_LINK_FLAGS    "-mwindows")
#
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(file_debug ${FILE_SYS} File_System/debug/file_debug.c)
add_executable(sound_debug ${SOUND} Sound/debug/sound_debug.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)
add_executable(Launcher WIN32 ${LIB} ${GUI} Launcher/launcher_main.c)
add_executable(leaderboard WIN32 ${LIB} ${GUI} ${FILE_SYS} Leader_Board/leaderboard_main.c)
add_executable(single_main WIN32 ${LIB} ${MODEL} ${VIEW} ${CONTROLLER} ${GUI} ${FILE_SYS} ${SOUND} single_src/single_main.c)


target_link_libraries(sound_debug winmm.lib)
target_link_libraries(Launcher winmm.lib)
target_link_libraries(single_main winmm.lib)