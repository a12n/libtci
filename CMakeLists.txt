cmake_minimum_required(VERSION 2.6)

project(tci)

option(TCI_WITH_SHARED
  "Build shared library."
  OFF)

if(TCI_WITH_SHARED)
  add_library(tci SHARED tci.cpp)
  set_target_properties(tci PROPERTIES SOVERSION "1.0.0")
else(TCI_WITH_SHARED)
  add_library(tci STATIC tci.cpp)
endif(TCI_WITH_SHARED)

install(FILES tci.hpp DESTINATION include)
install(TARGETS tci DESTINATION lib)
