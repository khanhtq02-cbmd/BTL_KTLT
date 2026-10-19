#include "Normalized.h"
#include <sstream>
#include <cctype>

namespace Normalized {

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

std::string CollapseSpace(const std::string& str) {
    std::string trimmed = trim(str);
    std::string result;
    bool inSpace = false;
    for (char c : trimmed) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!inSpace) { result += ' '; inSpace = true; }
        } else {
            result += c;
            inSpace = false;
        }
    }
    return result;
}

std::string removeSymbols(const std::string& str) {
    const std::string FORBIDDEN = "|{}><~`#@!%^&*():;";
    std::string result = str;
    for (char& c : result)
        if (FORBIDDEN.find(c) != std::string::npos) c = ' ';
    return CollapseSpace(result);
}

std::string removeDigits(const std::string& str) {
    const std::string DIGITS = "0123456789";
    std::string result = str;
    for (char& c : result)
        if (DIGITS.find(c) != std::string::npos) c = ' ';
    return CollapseSpace(result);
}

std::string toLower(const std::string& str) {
    std::string result = str;
    for (char& c : result)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return result;
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    for (char& c : result)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return result;
}

std::string NormalizedName(const std::string& rawName) {
    std::istringstream iss(removeSymbols(rawName));
    std::string word, result;
    while (iss >> word) {
        word = toLower(word);
        word[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(word[0])));
        if (!result.empty()) result += ' ';
        result += word;
    }
    return result;
}

std::string NormalizedId(const std::string& rawId) {
    std::string cleaned = toUpper(trim(rawId));
    std::string digits;
    for (char c : cleaned)
        if (std::isdigit(static_cast<unsigned char>(c))) digits += c;
    return digits.empty() ? cleaned : digits;   
}

std::string NormalizedProvinceCode(const std::string& tinhLe) {
    std::string code;
    bool startOfWord = true;
    char last = 0;
    for (unsigned char c : tinhLe) {
        if (c == ' ') { startOfWord = true; continue; }
        if (startOfWord) code += static_cast<char>(std::toupper(c));
        startOfWord = false;
        last = static_cast<char>(std::toupper(c));
    }
    if (last) code += last;
    return code;
}

bool isValidPhoneNumber(const std::string& phone, bool allowUnassigned) {
    if (allowUnassigned && (phone.empty() || phone == "ChuaGan")) return true;
    if (phone.size() != 10 || phone[0] != '0') return false;
    if (std::string("35789").find(phone[1]) == std::string::npos) return false;
    for (char c : phone)
        if (c < '0' || c > '9') return false;
    return true;
}

bool isValidLuhn(const std::string& imeiStr) {
    if (imeiStr.length() != 15) return false;

    bool allZeros = true;
    for (char c : imeiStr) {
        if (c < '0' || c > '9') return false;
        if (c != '0') allZeros = false;
    }
    if (allZeros) return false;

    int sum = 0;
    for (int i = 14; i >= 0; --i) {
        int d = imeiStr[i] - '0';
        int posFromRight = 15 - i;
        if (posFromRight % 2 == 0) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        sum += d;
    }
    return (sum % 10 == 0);
}

} // namespace Normalized
