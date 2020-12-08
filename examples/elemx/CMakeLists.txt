set(PROJECT_NAME elemx)
project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES
        src/*.h
        src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE elem)
target_link_libraries(${PROJECT_NAME} PRIVATE elemd::elemd)

# Make res folder available inside the cmake build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples/elemx/res ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT "Copying resource files"
)