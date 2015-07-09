cmake_minimum_required(VERSION 2.6)

project(libtci)

option(LIBTCI_WITH_SHARED
  "Build shared library."
  OFF)

if(LIBTCI_WITH_SHARED)
  add_library(tci SHARED tci.cpp)
  set_target_properties(tci PROPERTIES SOVERSION "3.1.0")
else(LIBTCI_WITH_SHARED)
  add_library(tci STATIC tci.cpp)
endif(LIBTCI_WITH_SHARED)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-keywords")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
endif(CMAKE_COMPILER_IS_GNUCXX)

install(FILES tci.hpp tci2.hpp DESTINATION include)
install(TARGETS tci DESTINATION lib)
