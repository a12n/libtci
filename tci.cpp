// License: WTFPL (http://www.wtfpl.net/)

#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "tci.hpp"

namespace config {

std::string base_path = "/etc/config/";

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
        while (i.good()) {
            std::getline(i, t);
            x.push_back(t);
        }
        return !i.bad() && (!i.fail() || !x.empty());
    }
};

//----------------------------------------------------------------------------

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
        o << '\n';
        return o.good();
    }
};

} // namespace

template <class T>
bool
get(const std::string& path, T& ans)
{
    std::ifstream ifs((base_path + path).c_str(), std::ios_base::in);
    return get_impl<T>()(ifs, ans);
}

template bool get<float>(const std::string&, float&);
template bool get<int>(const std::string&, int&);
template bool get<std::string>(const std::string&, std::string&);
template bool get<std::vector<float> >(const std::string&, std::vector<float>&);
template bool get<std::vector<int> >(const std::string&, std::vector<int>&);
template bool get<std::vector<std::string> >(const std::string&, std::vector<std::string>&);

//----------------------------------------------------------------------------

template <class T>
bool
set(const std::string& path, const T& val)
{
    std::ofstream ofs((base_path + path).c_str(), std::ios_base::out | std::ios_base::trunc);
    return set_impl<T>()(ofs, val);
}

template bool set<float>(const std::string&, const float&);
template bool set<int>(const std::string&, const int&);
template bool set<std::string>(const std::string&, const std::string&);
template bool set<std::vector<float> >(const std::string&, const std::vector<float>&);
template bool set<std::vector<int> >(const std::string&, const std::vector<int>&);
template bool set<std::vector<std::string> >(const std::string&, const std::vector<std::string>&);

//----------------------------------------------------------------------------

template <class T>
T
value(const std::string& path)
{
    T ans;

    if (!get<T>(path, ans)) {
        throw std::runtime_error("Unable to read '" + path + "' value");
    }
    return ans;
}

template float value<float>(const std::string&);
template int value<int>(const std::string&);
template std::string value<std::string>(const std::string&);
template std::vector<float> value<std::vector<float> >(const std::string&);
template std::vector<int> value<std::vector<int> >(const std::string&);
template std::vector<std::string> value<std::vector<std::string> >(const std::string&);

//----------------------------------------------------------------------------

template <class T>
T
value(const std::string& path, const T& def)
{
    try {
        return value<T>(path);
    } catch (const std::runtime_error&) {
        return def;
    }
}

template float value<float>(const std::string&, const float&);
template int value<int>(const std::string&, const int&);
template std::string value<std::string>(const std::string&, const std::string&);
template std::vector<float> value<std::vector<float> >(const std::string&, const std::vector<float>&);
template std::vector<int> value<std::vector<int> >(const std::string&, const std::vector<int>&);
template std::vector<std::string> value<std::vector<std::string> >(const std::string&, const std::vector<std::string>&);

} // namespace config
