cmake_minimum_required(VERSION 3.14)

project(cppCodeFeaturesExtractor)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

include_directories(${CMAKE_SOURCE_DIR}/vendor/include)

add_subdirectory(src)
add_subdirectory(vendor)