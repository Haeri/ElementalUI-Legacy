set(PROJECT_NAME calculator)
project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES
        src/*.h
        src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE elem)
target_link_libraries(${PROJECT_NAME} PRIVATE elemd::elemd)