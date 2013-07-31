// License: WTFPL (http://www.wtfpl.net/)

#include <cstring>
#include <fstream>
#include <stdexcept>

#include "tci.hpp"

namespace config {

template <class T>
bool
get(const std::string& path, T& ans)
{
    std::ifstream ifs((base_path + path).c_str(), std::ios_base::in);

    ifs >> ans;
    return !ifs.bad() && !ifs.fail();
}

template <>
bool
get<std::string>(const std::string& path, std::string& ans)
{
    std::ifstream ifs((base_path + path).c_str(), std::ios_base::in);

    std::getline(ifs, ans);
    return !ifs.bad() && !ifs.fail();
}

template bool get<int>(const std::string&, int&);
template bool get<std::string>(const std::string&, std::string&);

//----------------------------------------------------------------------------

template <class T>
bool
set(const std::string& path, const T& val)
{
    std::ofstream ofs((base_path + path).c_str(), std::ios_base::out | std::ios_base::trunc);

    ofs << val << '\n';
    return ofs.good();
}

template bool set<int>(const std::string&, const int&);
template bool set<std::string>(const std::string&, const std::string&);

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

template int value<int>(const std::string&);
template std::string value<std::string>(const std::string&);

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

template int value<int>(const std::string&, const int&);
template std::string value<std::string>(const std::string&, const std::string&);

} // namespace config
