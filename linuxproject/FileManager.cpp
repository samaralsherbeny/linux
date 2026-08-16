#include "FileManager.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cerrno>
#include <cstring>

namespace {
std::string permissionString(mode_t mode) {
    std::string p = "----------";
    if (S_ISDIR(mode)) p[0] = 'd';
    if (S_ISLNK(mode)) p[0] = 'l';
    if (mode & S_IRUSR) p[1] = 'r';
    if (mode & S_IWUSR) p[2] = 'w';
    if (mode & S_IXUSR) p[3] = 'x';
    if (mode & S_IRGRP) p[4] = 'r';
    if (mode & S_IWGRP) p[5] = 'w';
    if (mode & S_IXGRP) p[6] = 'x';
    if (mode & S_IROTH) p[7] = 'r';
    if (mode & S_IWOTH) p[8] = 'w';
    if (mode & S_IXOTH) p[9] = 'x';
    return p;
}

void printFileInfo(const std::string& path) {
    struct stat st{};
    if (stat(path.c_str(), &st) != 0) {
        std::cerr << "stat failed: " << std::strerror(errno) << '\n';
        return;
    }

    struct passwd* owner = getpwuid(st.st_uid);
    struct group* group = getgrgid(st.st_gid);

    std::cout << "\nPath: " << path << '\n';
    std::cout << "Type: " << (S_ISREG(st.st_mode) ? "regular file" : S_ISDIR(st.st_mode) ? "directory" : "other") << '\n';
    std::cout << "Size: " << st.st_size << " bytes\n";
    std::cout << "Owner: " << (owner ? owner->pw_name : std::to_string(st.st_uid)) << '\n';
    std::cout << "Group: " << (group ? group->gr_name : std::to_string(st.st_gid)) << '\n';
    std::cout << "Permissions: " << permissionString(st.st_mode) << '\n';
    std::cout << "Last modified: " << std::ctime(&st.st_mtime);
}
}

void FileManager::showFileInfo(const std::string& path) const {
    std::cout << "\n=== File Info ===\n";
    printFileInfo(path);
}

void FileManager::showFilePermissions(const std::string& path) const {
    struct stat st{};
    if (stat(path.c_str(), &st) != 0) {
        std::cerr << "stat failed: " << std::strerror(errno) << '\n';
        return;
    }
    std::cout << "Permissions for " << path << ": " << permissionString(st.st_mode)
              << " (octal " << std::oct << (st.st_mode & 0777) << std::dec << ")\n";
}

void FileManager::changeFilePermissions(const std::string& path, unsigned int mode) const {
    if (mode > 0777) {
        std::cerr << "Mode must be between 000 and 777 (octal).\n";
        return;
    }
    if (chmod(path.c_str(), static_cast<mode_t>(mode)) != 0) {
        std::cerr << "chmod failed: " << std::strerror(errno) << '\n';
        return;
    }
    std::cout << "Permissions changed successfully.\n";
    showFilePermissions(path);
}
