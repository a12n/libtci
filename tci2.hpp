// License: WTFPL (http://www.wtfpl.net/)

#pragma once

#ifndef __TCI2_HPP_INCLUDED__
#define __TCI2_HPP_INCLUDED__

#include <string>

namespace tci {

// Instantiated only for types:
//  bool
//  float
//  int
//  std::string
//  std::vector<bool>
//  std::vector<float>
//  std::vector<int>
//  std::vector<std::string>

class config
{
public:
    explicit
    config(const std::string& base = "/etc/config/");

    template <class T>
    bool
    get(const std::string& path, T& ans) const;

    template <class T>
    void
    set(const std::string& path, const T& val);

    template <class T>
    T
    value(const std::string& path) const;

    template <class T>
    T
    value(const std::string& path, const T& def) const;

private:
    const std::string base_;
};

//----------------------------------------------------------------------------

template <class T>
bool
get(const std::string& path, T& ans)
{
    return config().get<T>(path, ans);
}

template <class T>
void
set(const std::string& path, const T& val)
{
    config().set<T>(path, val);
}

template <class T>
T
value(const std::string& path)
{
    return config().value<T>(path);
}

template <class T>
T
value(const std::string& path, const T& def)
{
    return config().value<T>(path, def);
}

} // namespace tci

#endif  // __TCI2_HPP_INCLUDED__
