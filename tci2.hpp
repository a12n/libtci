// License: WTFPL (http://www.wtfpl.net/)

#pragma once

#ifndef __TCI2_HPP_INCLUDED__
#define __TCI2_HPP_INCLUDED__

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace tci {

//----------------------------------------------------------------------------
// Read/write configuration entries

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
// Read/write configuration entries in /etc/config/.

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

//----------------------------------------------------------------------------
// Implementation details

namespace internal {

// Get value
template <class T>
struct get_impl
{
    bool
    operator()(std::istream& i, T& x) const
    {
        i >> x;
        return !i.bad() && !i.fail();
    }
};

// Get list of values
template <class T>
struct get_impl<std::vector<T> >
{
    bool
    operator()(std::istream& i, std::vector<T>& x) const
    {
        x.assign(std::istream_iterator<T>(i), std::istream_iterator<T>());
        return !i.bad() && (!i.fail() || !x.empty());
    }
};

// Get line
template <>
struct get_impl<std::string>
{
    bool
    operator()(std::istream& i, std::string& x) const
    {
        std::getline(i, x);
        return !i.bad() && !i.fail();
    }
};

// Get list of lines
template <>
struct get_impl<std::vector<std::string> >
{
    bool
    operator()(std::istream& i, std::vector<std::string>& x) const
    {
        std::string t;
        x.clear();
        while (std::getline(i, t).good()) {
            x.push_back(t);
        }
        return !i.bad() && (!i.fail() || !x.empty());
    }
};

// Set value
template <class T>
struct set_impl
{
    bool
    operator()(std::ostream& o, const T& x) const
    {
        o << x << '\n';
        return o.good();
    }
};

// Set list of values
template <class T>
struct set_impl<std::vector<T> >
{
    bool
    operator()(std::ostream& o, const std::vector<T>& x) const
    {
        std::copy(x.begin(), x.end(), std::ostream_iterator<T>(o, "\n"));
        return o.good();
    }
};

} // namespace internal

config::config(const std::string& base) :
    base_(base)
{
}

template <class T>
bool
config::get(const std::string& path, T& ans) const
{
    std::ifstream ifs((base_ + path).c_str(), std::ios_base::in);
    return internal::get_impl<T>()(ifs, ans);
}

template <class T>
void
config::set(const std::string& path, const T& val)
{
    std::ofstream ofs((base_ + path).c_str(), std::ios_base::out | std::ios_base::trunc);
    if (!internal::set_impl<T>()(ofs, val)) {
        throw std::runtime_error(path);
    }
}

template <class T>
T
config::value(const std::string& path) const
{
    T ans;
    if (!get<T>(path, ans)) {
        throw std::runtime_error(path);
    }
    return ans;
}

template <class T>
T
config::value(const std::string& path, const T& def) const
{
    try {
        return value<T>(path);
    } catch (const std::runtime_error&) {
        return def;
    }
}

} // namespace tci

#endif  // __TCI2_HPP_INCLUDED__
