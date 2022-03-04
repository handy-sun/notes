cmake_minimum_required(VERSION 2.8)

project(singly LANGUAGES C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(EXE_NAME ${PROJECT_NAME})
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(EXE_NAME "${EXE_NAME}_D")
endif()

set(SRC
    singlyLinkedList.h
    singlyLinkedList.c
    main.c
)

add_executable(${PROJECT_NAME} ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME})

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m)
endif()
