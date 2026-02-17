cmake_minimum_required(VERSION 3.5)

project(OlifreGB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++03 -static")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLM REQUIRED)
find_package(glad REQUIRED)

include_directories(include ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS})

file(GLOB SOURCES
    src/*.cpp
    src/GB/*.cpp
    src/GB/memory/*.cpp
    src/GB/memory/MBC/*.cpp 
    src/GB/memory/registers/*.cpp 
    src/window/*.cpp
    src/lib/*.cpp
    src/test/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE_FILE})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${GLFW3_LIBRARIES} opengl32 gdi32 user32)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_OS)
elseif(UNIX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNIX_OS)
endif()