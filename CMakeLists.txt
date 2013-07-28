cmake_minimum_required(VERSION 2.6)

project(libconfig)

option(LIBCONFIG_WITH_SHARED
  "Build shared library."
  OFF)

if(LIBCONFIG_WITH_SHARED)
  add_library(config SHARED config.cpp)
  set_target_properties(config PROPERTIES SOVERSION "0.1.0")
else(LIBCONFIG_WITH_SHARED)
  add_library(config STATIC config.cpp)
endif(LIBCONFIG_WITH_SHARED)

install(FILES config.hpp DESTINATION include)
install(TARGETS config DESTINATION lib)
