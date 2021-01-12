set(PROJECT_NAME slack)
project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES
        src/*.h
        src/*.cpp)


#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $<$<CONFIG:RELEASE>:/SUBSYSTEM:WINDOWS /ENTRY\:mainCRTStartup>")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE elem)
target_link_libraries(${PROJECT_NAME} PRIVATE elemd::elemd)

# Make res folder available inside the cmake build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples/slack/res ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT "Copying resource files"
)