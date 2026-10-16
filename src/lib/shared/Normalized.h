#ifndef NORMALIZED_H
#define NORMALIZED_H

#include <string>

namespace Normalized {
    std::string trim(const std::string& str);
    std::string CollapseSpace(const std::string& str);
    std::string removeSymbols(const std::string& str);
    std::string removeDigits(const std::string& str);
    std::string toLower(const std::string& str);
    std::string toUpper(const std::string& str);

    std::string NormalizedName(const std::string& str);
    std::string NormalizedId(const std::string& str);
    std::string NormalizedProvinceCode(const std::string& str);
    bool isValidPhoneNumber(const std::string& phone, bool allowUnassigned = false);
}

#endif // NORMALIZED_H
