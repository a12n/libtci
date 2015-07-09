// License: WTFPL (http://www.wtfpl.net/)

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "tci2.hpp"

namespace tci {
namespace {

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

} // namespace

config::config(const std::string& base) :
    base_(base)
{
}

template <class T>
bool
config::get(const std::string& path, T& ans) const
{
    std::ifstream ifs((base_ + path).c_str(), std::ios_base::in);
    return get_impl<T>()(ifs, ans);
}

template bool config::get<bool>(const std::string&, bool&) const;
template bool config::get<float>(const std::string&, float&) const;
template bool config::get<int>(const std::string&, int&) const;
template bool config::get<std::string>(const std::string&, std::string&) const;
template bool config::get<std::vector<bool> >(const std::string&, std::vector<bool>&) const;
template bool config::get<std::vector<float> >(const std::string&, std::vector<float>&) const;
template bool config::get<std::vector<int> >(const std::string&, std::vector<int>&) const;
template bool config::get<std::vector<std::string> >(const std::string&, std::vector<std::string>&) const;

template <class T>
void
config::set(const std::string& path, const T& val)
{
    std::ofstream ofs((base_ + path).c_str(), std::ios_base::out | std::ios_base::trunc);
    if (!set_impl<T>()(ofs, val)) {
        throw std::runtime_error(path);
    }
}

template void config::set<bool>(const std::string&, const bool&);
template void config::set<float>(const std::string&, const float&);
template void config::set<int>(const std::string&, const int&);
template void config::set<std::string>(const std::string&, const std::string&);
template void config::set<std::vector<bool> >(const std::string&, const std::vector<bool>&);
template void config::set<std::vector<float> >(const std::string&, const std::vector<float>&);
template void config::set<std::vector<int> >(const std::string&, const std::vector<int>&);
template void config::set<std::vector<std::string> >(const std::string&, const std::vector<std::string>&);

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

template bool config::value<bool>(const std::string&) const;
template float config::value<float>(const std::string&) const;
template int config::value<int>(const std::string&) const;
template std::string config::value<std::string>(const std::string&) const;
template std::vector<bool> config::value<std::vector<bool> >(const std::string&) const;
template std::vector<float> config::value<std::vector<float> >(const std::string&) const;
template std::vector<int> config::value<std::vector<int> >(const std::string&) const;
template std::vector<std::string> config::value<std::vector<std::string> >(const std::string&) const;

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

template bool config::value<bool>(const std::string&, const bool&) const;
template float config::value<float>(const std::string&, const float&) const;
template int config::value<int>(const std::string&, const int&) const;
template std::string config::value<std::string>(const std::string&, const std::string&) const;
template std::vector<bool> config::value<std::vector<bool> >(const std::string&, const std::vector<bool>&) const;
template std::vector<float> config::value<std::vector<float> >(const std::string&, const std::vector<float>&) const;
template std::vector<int> config::value<std::vector<int> >(const std::string&, const std::vector<int>&) const;
template std::vector<std::string> config::value<std::vector<std::string> >(const std::string&, const std::vector<std::string>&) const;

} // namespace tci
