#pragma once
#include <string>

class FileManager {
public:
    void showFileInfo(const std::string& path) const;
    void showFilePermissions(const std::string& path) const;
    void changeFilePermissions(const std::string& path, unsigned int mode) const;
};
