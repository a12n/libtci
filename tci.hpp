// License: WTFPL (http://www.wtfpl.net/)

// Deprecated. Always include "tci.hpp" but use API from "tci2.hpp".

#pragma once

#ifndef __TCI_HPP_INCLUDED__
#define __TCI_HPP_INCLUDED__

#include <stdexcept>

#include "tci2.hpp"

namespace config {

extern std::string base_path;

template <class T>
bool
get(const std::string& path, T& ans)
{
    return tci::config(base_path).get<T>(path, ans);
}

template <class T>
bool
set(const std::string& path, const T& val)
{
    try {
        tci::config(base_path).set<T>(path, val);
        return true;
    } catch (const std::runtime_error&) {
        return false;
    }
}

template <class T>
T
value(const std::string& path)
{
    return tci::config(base_path).value<T>(path);
}

template <class T>
T
value(const std::string& path, const T& def)
{
    return tci::config(base_path).value<T>(path, def);
}

} // namespace config

#endif  // __TCI_HPP_INCLUDED__
