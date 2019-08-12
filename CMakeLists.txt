cmake_minimum_required(VERSION 3.1)
project(botanProjekt)

set(CMAKE_CXX_STANDARD 17)
add_executable(botanProjekt main.cpp Sources/User_Interface.cpp Header/User_Interface.h dateiVerschluesselung.cpp dateiVerschluesselung.h)
set(CMAKE_CXX_FLAGS -pthread)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Lib/libbotan-2.a)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Lib/libboost_unit_test_framework.a)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Lib)






add_executable(tester Tests/loginTest.cpp)

enable_testing()
target_link_libraries(tester ${PROJECT_SOURCE_DIR}/Lib/libbotan-2.a)
target_link_libraries(tester ${PROJECT_SOURCE_DIR}/Lib/libboost_unit_test_framework.a)
target_include_directories(tester PUBLIC ${PROJECT_SOURCE_DIR}/Lib)

add_test(Tester tester)