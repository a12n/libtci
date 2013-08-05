// License: WTFPL (http://www.wtfpl.net/)

#pragma once

#ifndef __TCI_HPP_INCLUDED__
#define __TCI_HPP_INCLUDED__

#include <string>

namespace config {

const std::string base_path = "/etc/config/";

// Instantiated only for types:
//  float
//  int
//  std::string
//  std::vector<float>
//  std::vector<int>
//  std::vector<std::string>

template <class T>
bool
get(const std::string& path, T& ans);

template <class T>
bool
set(const std::string& path, const T& val);

template <class T>
T
value(const std::string& path);

template <class T>
T
value(const std::string& path, const T& def);

} // namespace config

#endif  // __TCI_HPP_INCLUDED__
