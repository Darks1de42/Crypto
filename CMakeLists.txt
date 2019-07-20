cmake_minimum_required(VERSION 3.14)
project(botanProjekt)

set(CMAKE_CXX_STANDARD 17)
add_executable(botanProjekt main.cpp Sources/User_Interface.cpp Header/User_Interface.h)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Lib/libbotan-2.a)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Lib)
