# Linux System Manager – C++

A terminal-based Linux system manager implemented in C++17. It demonstrates Linux/POSIX concepts including system information, memory, disk, CPU, processes, process creation, signals, IPC with pipes, files and permissions, networking, DNS, ping, and multithreading.

## Build

```bash
sudo apt update
sudo apt install build-essential cmake iputils-ping

cd linux_system_manager
mkdir -p build
cd build
cmake ..
cmake --build .
./linux_system_manager
```

## Main features

1. Linux commands: `pwd`, `ls -l`, `whoami`, `df -h`, `ps aux`
2. System information: kernel, architecture, hostname, current user
3. OS information: `/etc/os-release`
4. Memory information: `sysinfo()`
5. Disk information: `statvfs()`
6. CPU information: `/proc/cpuinfo`, `/proc/loadavg`
7. Process list and process details from `/proc`
8. Child process creation with `fork()`
9. Signals with `kill()`
10. IPC using `pipe()` + `fork()` + `read()`/`write()`
11. File information and permissions using `stat()`
12. File permissions change using `chmod()`
13. Network interfaces using `getifaddrs()`
14. DNS lookup using `getaddrinfo()`
15. Ping using the Linux `ping` utility
16. Multithreading using `std::thread`

## Notes

- Run on Linux or WSL. Some `/proc` information can vary between distributions.
- The signal feature is intentionally limited to SIGINT, SIGTERM and SIGKILL for the project.
- Only send signals to processes you own or have permission to manage.
