cmake_minimum_required(VERSION 3.5)

project(OlifreGB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++03 -static")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLM REQUIRED)
find_package(glad REQUIRED)

include_directories(include ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp src/GB/*.cpp src/GB/opcodes/*.cpp src/window/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE_FILE})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${GLFW3_LIBRARIES})