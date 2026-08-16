#include "SystemManager.h"
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <pwd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace {
void printBytes(unsigned long long bytes) {
    const char* units[] = {"B", "KB", "MB", "GB", "TB"};
    double value = static_cast<double>(bytes);
    int unit = 0;
    while (value >= 1024.0 && unit < 4) {
        value /= 1024.0;
        ++unit;
    }
    std::cout << std::fixed << std::setprecision(2) << value << ' ' << units[unit];
}
}

void SystemManager::showSystemInfo() const {
    struct utsname info{};
    if (uname(&info) != 0) {
        perror("uname");
        return;
    }

    char hostname[256]{};
    if (gethostname(hostname, sizeof(hostname) - 1) != 0) {
        std::snprintf(hostname, sizeof(hostname), "unknown");
    }

    struct passwd* pw = getpwuid(getuid());

    std::cout << "\n=== System Info ===\n";
    std::cout << "OS: " << info.sysname << '\n';
    std::cout << "Kernel: " << info.release << '\n';
    std::cout << "Kernel version: " << info.version << '\n';
    std::cout << "Architecture: " << info.machine << '\n';
    std::cout << "Hostname: " << hostname << '\n';
    std::cout << "Current user: " << (pw ? pw->pw_name : "unknown") << '\n';
    std::cout << "User ID: " << getuid() << '\n';
}

void SystemManager::showOSInfo() const {
    std::ifstream file("/etc/os-release");
    if (!file) {
        std::cerr << "Cannot open /etc/os-release\n";
        return;
    }

    std::cout << "\n=== OS Info (/etc/os-release) ===\n";
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0 ||
            line.rfind("NAME=", 0) == 0 ||
            line.rfind("VERSION=", 0) == 0 ||
            line.rfind("VERSION_ID=", 0) == 0) {
            std::cout << line << '\n';
        }
    }
}

void SystemManager::showMemoryInfo() const {
    struct sysinfo info{};
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return;
    }

    unsigned long long total = static_cast<unsigned long long>(info.totalram) * info.mem_unit;
    unsigned long long free = static_cast<unsigned long long>(info.freeram) * info.mem_unit;
    unsigned long long available = static_cast<unsigned long long>(info.freeram + info.bufferram) * info.mem_unit;
    unsigned long long used = total > free ? total - free : 0;

    std::cout << "\n=== Memory Info ===\n";
    std::cout << "Total RAM: "; printBytes(total); std::cout << '\n';
    std::cout << "Free RAM:  "; printBytes(free); std::cout << '\n';
    std::cout << "Approx. used RAM: "; printBytes(used); std::cout << '\n';
    std::cout << "Free + buffers: "; printBytes(available); std::cout << '\n';
}

void SystemManager::showDiskInfo() const {
    struct statvfs stat{};
    if (statvfs("/", &stat) != 0) {
        perror("statvfs");
        return;
    }

    unsigned long long total = static_cast<unsigned long long>(stat.f_blocks) * stat.f_frsize;
    unsigned long long free = static_cast<unsigned long long>(stat.f_bfree) * stat.f_frsize;
    unsigned long long available = static_cast<unsigned long long>(stat.f_bavail) * stat.f_frsize;

    std::cout << "\n=== Disk Info: / ===\n";
    std::cout << "Total:     "; printBytes(total); std::cout << '\n';
    std::cout << "Free:      "; printBytes(free); std::cout << '\n';
    std::cout << "Available: "; printBytes(available); std::cout << '\n';
}

void SystemManager::showCPUInfo() const {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::ifstream loadavg("/proc/loadavg");

    std::string model;
    int cores = 0;
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.rfind("model name", 0) == 0 && model.empty()) {
            auto pos = line.find(':');
            if (pos != std::string::npos) model = line.substr(pos + 2);
        }
        if (line.rfind("processor", 0) == 0) ++cores;
    }

    std::string load;
    std::getline(loadavg, load);

    std::cout << "\n=== CPU Info ===\n";
    std::cout << "CPU model: " << (model.empty() ? "unknown" : model) << '\n';
    std::cout << "Logical CPUs: " << cores << '\n';
    std::cout << "Load average: " << (load.empty() ? "unknown" : load) << '\n';
}
