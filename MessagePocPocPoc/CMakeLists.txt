project(MessagePocPocPoc)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
aux_source_directory(./msg SRC_LIST1)

if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -std=c++11")
endif()

add_executable(${PROJECT_NAME} ${SRC_LIST} ${SRC_LIST1})

