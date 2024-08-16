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
# target_link_libraries(${CMAKE_PROJECT_NAME}  /home/lrx/codes/quantum/lib/python3.12/libpython3.12.so.1.0)
target_link_libraries(${CMAKE_PROJECT_NAME}  /Users/liruixiang/codes/quantum/lib/python3.12/libpython3.12.dylib)

# target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${HEADER_DIRS})

include_directories(${CMAKE_PROJECT_NAME} ${HEADER_DIRS})

include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/OpenXLSX)

# 引入python库
include_directories(../include/python3.12)

# 假设你有一个叫做 MyProject 的目标
get_target_property(INCLUDE_DIRS ${CMAKE_PROJECT_NAME} INCLUDE_DIRECTORIES)

# 打印 include_directories
# message(STATUS "Include directories for target ${CMAKE_PROJECT_NAME}: ${INCLUDE_DIRS}")

# 打印 src_directories
# message(STATUS "Src directories for target ${CMAKE_PROJECT_NAME}: ${SRC_LIST}")