set(PROJECT_NAME calculator)
project(${PROJECT_NAME})

if(WIN32) 
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc")
else()
    set(APP_ICON_RESOURCE_WINDOWS "")
endif()

file(GLOB_RECURSE SOURCE_FILES
        src/*.hpp
        src/*.cpp
        ${APP_ICON_RESOURCE_WINDOWS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE elem)
target_link_libraries(${PROJECT_NAME} PRIVATE elemd::elemd)

# Make res folder available inside the cmake build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples/calculator/res ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT "Copying resource files"
)