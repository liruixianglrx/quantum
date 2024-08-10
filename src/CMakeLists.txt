cmake_minimum_required(VERSION 3.15)

file(GLOB_RECURSE SRC_LIST
    "./*.cpp"
)

#include headers
file(GLOB INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include/*")
set(HEADER_DIRS)
foreach(dir ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${dir})
        list(APPEND HEADER_DIRS ${dir})
    endif()
endforeach()

#include cpps
add_executable(${CMAKE_PROJECT_NAME} ${SRC_LIST})

#add lib
target_link_libraries(${CMAKE_PROJECT_NAME}  OpenXLSX::OpenXLSX)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${HEADER_DIRS})