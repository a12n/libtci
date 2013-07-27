#include <fstream>
#include <stdexcept>

#include "config.hpp"

namespace config {

template <class T>
bool
get(const std::string& path, T& ans)
{
    std::ifstream ifs((base_path + path).c_str(), std::ios_base::in);

    if (ifs.good()) {
        ifs >> ans;
        return true;
    }
    return false;
}

template <>
bool
get<std::string>(const std::string& path, std::string& ans)
{
    std::ifstream ifs((base_path + path).c_str(), std::ios_base::in);

    if (ifs.good()) {
        std::getline(ifs, ans);
        return true;
    }
    return false;
}

template bool get<int>(const std::string&, int&);
template bool get<std::string>(const std::string&, std::string&);

//----------------------------------------------------------------------------

template <class T>
bool
set(const std::string& path, const T& val)
{
    std::ofstream ofs((base_path + path).c_str(), std::ios_base::out | std::ios_base::trunc);

    if (ofs.good()) {
        ofs << val << '\n';
        return true;
    }
    return false;
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
        throw std::runtime_error("Value '" + path + "' not found");
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

