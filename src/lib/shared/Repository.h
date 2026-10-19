#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include "fileio.h"
#include "Normalized.h"
#include "Exceptions.h"

namespace RepositoryConstants {
    const std::string TEMP_FILE_EXTENSION = ".tmp";
}

template <typename T>
class Repository {
private:
    std::string filePath;
    std::vector<T> items;

public:
    explicit Repository(const std::string& path) : filePath(path) {}

    const std::string& getFilePath() const { return filePath; }
    size_t size() const { return items.size(); }
    bool empty() const { return items.empty(); }

    std::vector<T>& getAll() { return items; }
    const std::vector<T>& getAll() const { return items; }

    bool loadFromFile() {
        FileIO::ensureDirectoryExists(filePath);
        std::ifstream inFile(filePath);
        if (!inFile.is_open()) {
            return false;
        }

        std::vector<T> loadedItems;
        std::string line;
        while (std::getline(inFile, line)) {
            std::string trimmedLine = Normalized::trim(line);
            if (trimmedLine.empty() || trimmedLine[0] == FileConstants::COMMENT_PREFIX) continue;
            T item;
            if (!item.fromFileString(trimmedLine)) continue;
            loadedItems.push_back(item);
        }
        if (inFile.bad()) {
            return false;
        }
        inFile.close();
        items.swap(loadedItems);
        return true;
    }
    //luu vao file
    bool saveToFile() const {
        FileIO::ensureDirectoryExists(filePath);
        std::string tempPath = FileIO::getTempStagingPath(filePath);
        std::ofstream outFile(tempPath);
        if (!outFile.is_open()) {
            throw FileIOException("Khong the mo tep tin tam tren tmps/ de ghi: " + tempPath);
        }

        for (const auto& item : items) {
            outFile << item.toFileString() << "\n";
        }
        outFile.flush();
        if (!outFile.good()) {
            outFile.close();
            std::remove(tempPath.c_str());
            throw FileIOException("Khong the ghi day du tep tin tam: " + tempPath);
        }
        outFile.close();
        if (outFile.fail()) {
            std::remove(tempPath.c_str());
            throw FileIOException("Khong the dong tep tin tam: " + tempPath);
        }

        //viet trong ram truoc,roi commit sang o cung
        if (!FileIO::commitFromTmp(tempPath, filePath)) {
            std::remove(tempPath.c_str());
            throw FileIOException("Khong the ghi de tep tin: " + filePath);
        }
        return true;
    }

    bool add(const T& item) {
        if (findById(item.getId()) != nullptr) {
            throw DuplicateIdException(item.getId());
        }
        items.push_back(item);
        try {
            return saveToFile();
        } catch (...) {
            items.pop_back();
            throw;
        }
    }

    bool update(const std::string& id, const T& updatedItem) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].getId() == id) {
                T previous = items[i];
                items[i] = updatedItem;
                try {
                    return saveToFile();
                } catch (...) {
                    items[i] = previous;
                    throw;
                }
            }
        }
        throw NotFoundException(id);
    }

    bool remove(const std::string& id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getId() == id) {
                const size_t index = static_cast<size_t>(it - items.begin());
                T previous = *it;
                items.erase(it);
                try {
                    return saveToFile();
                } catch (...) {
                    items.insert(items.begin() + index, previous);
                    throw;
                }
            }
        }
        throw NotFoundException(id);
    }

    T* findById(const std::string& id) {
        for (auto& item : items) {
            if (item.getId() == id) {
                return &item;
            }
        }
        return nullptr;
    }

    const T* findById(const std::string& id) const {
        for (const auto& item : items) {
            if (item.getId() == id) {
                return &item;
            }
        }
        return nullptr;
    }

    std::vector<T> filter(std::function<bool(const T&)> predicate) const {
        std::vector<T> result;
        for (const auto& item : items) {
            if (predicate(item)) {
                result.push_back(item);
            }
        }
        return result;
    }

    void sort(std::function<bool(const T&, const T&)> comparator) {
        std::sort(items.begin(), items.end(), comparator);
    }

    void clear() {
        std::vector<T> previous = items;
        items.clear();
        try {
            saveToFile();
        } catch (...) {
            items.swap(previous);
            throw;
        }
    }
};

#endif // REPOSITORY_H
