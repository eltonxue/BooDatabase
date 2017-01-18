cmake_minimum_required(VERSION 3.2)


set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



project(a.out.app)

include_directories(${CMAKE_SOURCE_DIR}/app)

file(GLOB APP_SRC_FILES ${CMAKE_SOURCE_DIR}/app/*.cpp)
file(GLOB APP_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/app/*.hpp)

set(APP_SRC_FILES_EXCEPT_MAIN ${APP_SRC_FILES})
list(REMOVE_ITEM APP_SRC_FILES_EXCEPT_MAIN ${CMAKE_SOURCE_DIR}/app/main.cpp)

add_definitions("-std=c++1z -stdlib=libc++ -Wall -g")

add_executable(${PROJECT_NAME} ${APP_SRC_FILES} ${APP_INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} c++ pthread) 



project(a.out.exp)

include_directories(${CMAKE_SOURCE_DIR}/app)
include_directories(${CMAKE_SOURCE_DIR}/exp)

file(GLOB EXP_SRC_FILES ${CMAKE_SOURCE_DIR}/exp/*.cpp)
file(GLOB EXP_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/exp/*.hpp)

add_definitions("-std=c++1z -stdlib=libc++ -Wall -g")

add_executable(${PROJECT_NAME} ${EXP_SRC_FILES} ${EXP_INCLUDE_FILES} ${APP_SRC_FILES_EXCEPT_MAIN} ${APP_INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} c++ pthread)



project(a.out.gtest)

include_directories(${CMAKE_SOURCE_DIR}/gtest)

file(GLOB GTEST_SRC_FILES ${CMAKE_SOURCE_DIR}/gtest/*.cpp)
file(GLOB GTEST_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/gtest/*.hpp)

add_definitions("-std=c++1z -stdlib=libc++ -Wall -g")

add_executable(${PROJECT_NAME} ${GTEST_SRC_FILES} ${GTEST_INCLUDE_FILES} ${APP_SRC_FILES_EXCEPT_MAIN} ${APP_INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} pthread c++ gtest gtest_main)

