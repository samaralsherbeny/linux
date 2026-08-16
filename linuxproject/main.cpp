#include "SystemManager.h"
#include "ProcessManager.h"
#include "FileManager.h"
#include "NetworkManager.h"
#include "IPCManager.h"
#include "ThreadManager.h"

#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>

namespace {
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        clearInput();
        std::cout << "Please enter a number.\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void linuxCommandsMenu() {
    while (true) {
        std::cout << "\n=== Linux Commands ===\n"
                  << "1. pwd\n"
                  << "2. ls -l\n"
                  << "3. whoami\n"
                  << "4. df -h\n"
                  << "5. ps aux (first 20 lines)\n"
                  << "0. Back\n";
        int choice = readInt("Choice: ");
        const char* command = nullptr;
        switch (choice) {
            case 1: command = "pwd"; break;
            case 2: command = "ls -l"; break;
            case 3: command = "whoami"; break;
            case 4: command = "df -h"; break;
            case 5: command = "ps aux | head -n 20"; break;
            case 0: return;
            default: std::cout << "Invalid choice.\n"; continue;
        }
        std::cout << "\n$ " << command << "\n";
        std::system(command);
    }
}

void systemMenu(SystemManager& sm) {
    while (true) {
        std::cout << "\n=== System ===\n"
                  << "1. System info\n"
                  << "2. OS info\n"
                  << "3. Memory info\n"
                  << "4. Disk info\n"
                  << "5. CPU info\n"
                  << "0. Back\n";
        int choice = readInt("Choice: ");
        switch (choice) {
            case 1: sm.showSystemInfo(); break;
            case 2: sm.showOSInfo(); break;
            case 3: sm.showMemoryInfo(); break;
            case 4: sm.showDiskInfo(); break;
            case 5: sm.showCPUInfo(); break;
            case 0: return;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void processMenu(ProcessManager& pm) {
    while (true) {
        std::cout << "\n=== Processes ===\n"
                  << "1. List processes\n"
                  << "2. Process info\n"
                  << "3. Create child process\n"
                  << "4. Send signal\n"
                  << "0. Back\n";
        int choice = readInt("Choice: ");
        switch (choice) {
            case 1: pm.listProcesses(); break;
            case 2: pm.showProcessInfo(readInt("PID: ")); break;
            case 3: pm.createChildProcess(); break;
            case 4: {
                int pid = readInt("PID: ");
                int sig = readInt("Signal (2=SIGINT, 15=SIGTERM, 9=SIGKILL): ");
                pm.sendSignal(pid, sig);
                break;
            }
            case 0: return;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void fileMenu(FileManager& fm) {
    while (true) {
        std::cout << "\n=== Files ===\n"
                  << "1. File info\n"
                  << "2. File permissions\n"
                  << "3. Change file permissions (chmod)\n"
                  << "0. Back\n";
        int choice = readInt("Choice: ");
        switch (choice) {
            case 1: fm.showFileInfo(readLine("Path: ")); break;
            case 2: fm.showFilePermissions(readLine("Path: ")); break;
            case 3: {
                std::string path = readLine("Path: ");
                std::cout << "Enter permission in octal, e.g. 644 or 755.\n";
                std::string text = readLine("Mode: ");
                try {
                    size_t pos = 0;
                    unsigned int mode = std::stoul(text, &pos, 8);
                    if (pos != text.size()) throw std::invalid_argument("bad");
                    fm.changeFilePermissions(path, mode);
                } catch (...) {
                    std::cout << "Invalid octal mode.\n";
                }
                break;
            }
            case 0: return;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void networkMenu(NetworkManager& nm) {
    while (true) {
        std::cout << "\n=== Network ===\n"
                  << "1. Network interfaces/info\n"
                  << "2. DNS lookup\n"
                  << "3. Ping host\n"
                  << "0. Back\n";
        int choice = readInt("Choice: ");
        switch (choice) {
            case 1: nm.showNetworkInfo(); break;
            case 2: nm.dnsLookup(readLine("Hostname: ")); break;
            case 3: nm.pingHost(readLine("Host/IP: ")); break;
            case 0: return;
            default: std::cout << "Invalid choice.\n";
        }
    }
}
}

int main() {
    SystemManager systemManager;
    ProcessManager processManager;
    FileManager fileManager;
    NetworkManager networkManager;
    IPCManager ipcManager;
    ThreadManager threadManager;

    std::cout << "==============================================\n";
    std::cout << "        LINUX SYSTEM MANAGER - C++\n";
    std::cout << "==============================================\n";

    while (true) {
        std::cout << "\nMain Menu\n"
                  << "1. Linux commands\n"
                  << "2. System information\n"
                  << "3. Processes\n"
                  << "4. Files & permissions\n"
                  << "5. IPC (pipe)\n"
                  << "6. Signals\n"
                  << "7. Network\n"
                  << "8. Multi-threaded example\n"
                  << "0. Exit\n";

        int choice = readInt("Choose an option: ");
        switch (choice) {
            case 1: linuxCommandsMenu(); break;
            case 2: systemMenu(systemManager); break;
            case 3: processMenu(processManager); break;
            case 4: fileMenu(fileManager); break;
            case 5: ipcManager.pipeExample(); break;
            case 6: {
                int pid = readInt("PID: ");
                int sig = readInt("Signal (2=SIGINT, 15=SIGTERM, 9=SIGKILL): ");
                processManager.sendSignal(pid, sig);
                break;
            }
            case 7: networkMenu(networkManager); break;
            case 8: threadManager.multiThreadExample(readInt("Number of threads (1-32): ")); break;
            case 0:
                std::cout << "Exiting Linux System Manager.\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
