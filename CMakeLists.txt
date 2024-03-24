cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME OlifreGB)
project(OlifreGB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++03 -static")

find_package(OpenGL REQUIRED)
include_directories(${PROJECT_NAME} ${OPENGL_INCLUDE_DIRS})

find_package(glfw3 REQUIRED)
include_directories(${PROJECT_NAME} ${GLFW3_INCLUDE_DIRS})

find_package(GLM REQUIRED)
include_directories(${PROJECT_NAME} ${GLM_INCLUDE_DIRS})

find_package(glad REQUIRED)
include_directories(${PROJECT_NAME} ${GLAD_INCLUDE_DIRS})


file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE_FILE})

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS}  ${GLAD_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${GLFW3_LIBRARIES})

# add_compile_definitions(GLEW_STATIC)