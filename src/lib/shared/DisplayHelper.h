#ifndef DISPLAY_HELPER_H
#define DISPLAY_HELPER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>

namespace DisplayHelper {

inline void printBorder(const std::vector<int>& widths, std::ostream& os = std::cout) {
    os << '+';
    for (int w : widths) os << std::string(w > 0 ? w : 1, '-') << '+';
    os << '\n';
}

inline void printRow(const std::vector<std::string>& cells,
                     const std::vector<int>& widths,
                     const std::vector<bool>& rightAlign = {},
                     std::ostream& os = std::cout) {
    os << '|';
    for (size_t i = 0; i < cells.size(); ++i) {
        int w = i < widths.size() ? widths[i] : static_cast<int>(cells[i].size()) + 2;
        if (i < rightAlign.size() && rightAlign[i])
            os << std::right << std::setw(w - 1) << cells[i] << " |";
        else
            os << ' ' << std::left << std::setw(w - 1) << cells[i] << '|';
    }
    os << '\n';
}

inline void printHeader(const std::vector<std::string>& headers,
                        const std::vector<int>& widths,
                        const std::vector<bool>& rightAlign = {},
                        std::ostream& os = std::cout) {
    printBorder(widths, os);
    printRow(headers, widths, rightAlign, os);
    printBorder(widths, os);
}

inline void printCard(const std::vector<std::pair<std::string, std::string>>& fields,
                      int labelWidth = 16,
                      std::ostream& os = std::cout) {
    const std::string line = "  " + std::string(50, '-') + '\n';
    os << line;
    for (const auto& field : fields)
        os << "  " << std::left << std::setw(labelWidth) << field.first << ": " << field.second << '\n';
    os << line;
}

} // namespace DisplayHelper

#endif // DISPLAY_HELPER_H