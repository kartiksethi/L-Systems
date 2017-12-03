cmake_minimum_required(VERSION 3.8)
project(LSystems)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        canvas.cpp
        canvas.h
        cfg.cpp
        cfg.h
        interpreter.cpp
        interpreter.h main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )

add_executable(LSystems ${SOURCE_FILES} cfg.cpp interpreter.cpp)
add_executable(main.cpp ${SOURCE_FILES})
target_link_libraries (main.cpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries (LSystems ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})