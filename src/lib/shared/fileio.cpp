#include "fileio.h"
#include "Normalized.h"
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

std::vector<std::string> FileIO::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(Normalized::trim(token));
    }
    if (!s.empty() && s.back() == delimiter) {
        tokens.push_back("");
    }
    return tokens;
}

bool FileIO::ensureDirectoryExists(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    if (pos == std::string::npos) return true;
    std::string dir = filepath.substr(0, pos);
#if defined(_WIN32)
    _mkdir(dir.c_str());
#else
    mkdir(dir.c_str(), 0755);
#endif
    return true;
}
