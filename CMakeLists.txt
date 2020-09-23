cmake_minimum_required(VERSION 3.3)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

set(PROJECT_NAME elemui)
project(${PROJECT_NAME} LANGUAGES CXX)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(ELEM_STANDALONE TRUE)
endif()

# Options
option(BUILD_SHARED_LIBS "Build as shared/dynamic library" ON)
option(ELEM_BUILD_EXAMPLES "Build the example programs" ${ELEM_STANDALONE})

# Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINE_HIDDEN YES)

# Enable folder view in solution explorer
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SOURCE_FILES
        include/${PROJECT_NAME}/*.hpp
        src/*.hpp
        src/*.cpp)

if (BUILD_SHARED_LIBS)
    add_compile_definitions(ELEM_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
    SOVERSION 0
    VERSION 0.0.1
)

target_include_directories(${PROJECT_NAME} PUBLIC include)



# ---------------- DEPENDENCIES ---------------------#

# elemd
find_package(elemd CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE elemd)