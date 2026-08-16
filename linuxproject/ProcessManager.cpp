#include "ProcessManager.h"
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cerrno>
#include <cstring>

namespace {
bool isNumber(const char* s) {
    if (!s || *s == '\0') return false;
    for (const char* p = s; *p; ++p) if (*p < '0' || *p > '9') return false;
    return true;
}

}

void ProcessManager::listProcesses() const {
    DIR* dir = opendir("/proc");
    if (!dir) {
        perror("opendir /proc");
        return;
    }

    std::vector<int> pids;
    while (dirent* entry = readdir(dir)) {
        if (isNumber(entry->d_name)) pids.push_back(std::stoi(entry->d_name));
    }
    closedir(dir);
    std::sort(pids.begin(), pids.end());

    std::cout << "\n=== Processes (PID / State / Name) ===\n";
    int shown = 0;
    for (int pid : pids) {
        std::ifstream statFile("/proc/" + std::to_string(pid) + "/stat");
        if (!statFile) continue;
        std::string line;
        std::getline(statFile, line);
        auto rightParen = line.rfind(')');
        if (rightParen == std::string::npos || rightParen + 2 >= line.size()) continue;
        std::string name = line.substr(line.find('(') + 1, rightParen - line.find('(') - 1);
        char state = line[rightParen + 2];
        std::cout << pid << "\t" << state << "\t" << name << '\n';
        if (++shown >= 100) {
            std::cout << "(First 100 processes shown.)\n";
            break;
        }
    }
}

void ProcessManager::showProcessInfo(int pid) const {
    std::string base = "/proc/" + std::to_string(pid);
    std::ifstream status(base + "/status");
    if (!status) {
        std::cerr << "Cannot read process " << pid << ". It may not exist or access may be denied.\n";
        return;
    }

    std::cout << "\n=== Process Info: " << pid << " ===\n";
    std::string line;
    while (std::getline(status, line)) {
        if (line.rfind("Name:", 0) == 0 ||
            line.rfind("State:", 0) == 0 ||
            line.rfind("Pid:", 0) == 0 ||
            line.rfind("PPid:", 0) == 0 ||
            line.rfind("Uid:", 0) == 0 ||
            line.rfind("VmSize:", 0) == 0 ||
            line.rfind("VmRSS:", 0) == 0 ||
            line.rfind("Threads:", 0) == 0) {
            std::cout << line << '\n';
        }
    }
}

int ProcessManager::createChildProcess() const {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        std::cout << "[Child] PID=" << getpid() << ", PPID=" << getppid() << "\n";
        std::cout << "[Child] Sleeping for 10 seconds. You can inspect it from the manager.\n";
        for (int i = 0; i < 10; ++i) sleep(1);
        _exit(0);
    }

    std::cout << "[Parent] Created child process with PID " << pid << "\n";
    std::cout << "The child will run for about 10 seconds.\n";
    return pid;
}

void ProcessManager::sendSignal(int pid, int signalNumber) const {
    if (signalNumber != SIGTERM && signalNumber != SIGINT && signalNumber != SIGKILL) {
        std::cerr << "For this project, use SIGTERM (15), SIGINT (2), or SIGKILL (9).\n";
        return;
    }

    if (kill(pid, signalNumber) == -1) {
        std::cerr << "kill() failed: " << std::strerror(errno) << '\n';
        return;
    }
    std::cout << "Signal " << signalNumber << " sent to PID " << pid << "\n";
}
