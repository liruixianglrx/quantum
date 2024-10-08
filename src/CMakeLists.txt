cmake_minimum_required(VERSION 3.15)

file(GLOB_RECURSE SRC_LIST
    "./*.cpp"
)
message(STATUS "files is ${SRC_LIST}")
if(WIN32)
    # Windows 特定设置
    set(IGNORE_FILES
    "${CMAKE_SOURCE_DIR}/src/./ADFTest/ADFTest.cpp"
    "${CMAKE_SOURCE_DIR}/src/./PlotTools/PlotTools.cpp"
    "${CMAKE_SOURCE_DIR}/src/./PlotTools/Plot.cpp"
    )
    list(REMOVE_ITEM SRC_LIST ${IGNORE_FILES})
endif()


message(STATUS "ignl is ${IGNORE_FILES}")
message(STATUS "files is ${SRC_LIST}")
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
if(UNIX AND NOT APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME}  /home/lrx/codes/quantum/lib/python3.12/libpython3.12.so.1.0)
elseif(APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME}  /Users/liruixiang/codes/quantum/lib/python3.12/libpython3.12.dylib)
endif()

# target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${HEADER_DIRS})

include_directories(${CMAKE_PROJECT_NAME} ${HEADER_DIRS})

include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/OpenXLSX)

# 引入python库
include_directories(../include/python3.12)

# 假设你有一个叫做 MyProject 的目标
get_target_property(INCLUDE_DIRS ${CMAKE_PROJECT_NAME} INCLUDE_DIRECTORIES)

# 打印 include_directories
# message(STATUS "Include directories for target ${CMAKE_PROJECT_NAME}: ${INCLUDE_DIRS}")
message(STATUS "os is ${CMAKE_SYSTEM_NAME}")
# 打印 src_directories
# message(STATUS "Src directories for target ${CMAKE_PROJECT_NAME}: ${SRC_LIST}")