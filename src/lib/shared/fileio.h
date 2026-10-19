#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>

namespace FilePaths {
    const std::string HOPDONG_DATA = "data/hopdong.txt";
    const std::string IMEI_DATA = "data/imei.txt";
    const std::string KHACHHANG_DATA = "data/khachhang.txt";
    const std::string GOICUOC_DATA = "data/CacGoiCuoc.txt";
    const std::string THUEBAO_DATA = "data/thuebao.txt";
    const std::string HOADON_DATA = "data/hoadon.txt";
    const std::string NAPTIEN_DATA = "data/naptien.txt";
    const std::string CDR_DATA = "data/cdr.txt";
    const std::string KHIEUNAI_DATA = "data/khieunai.txt";
    const std::string TMP_DIR = "tmps";
}

namespace FileConstants {
    const char DEFAULT_DELIMITER = '|';
    const char COMMENT_PREFIX = '#';
}

class FileIO {
public:
    static std::vector<std::string> split(const std::string& s, char delimiter = FileConstants::DEFAULT_DELIMITER);
    static bool ensureDirectoryExists(const std::string& filepath);
    static bool initTmpDir();
    static std::string getTempStagingPath(const std::string& targetFilePath);
    static bool commitFromTmp(const std::string& tmpPath, const std::string& targetPath);
    static bool isUsingTmpfs();
};

#endif // FILEIO_H
