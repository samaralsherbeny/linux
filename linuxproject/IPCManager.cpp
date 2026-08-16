#include "IPCManager.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

void IPCManager::pipeExample() const {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid == 0) {
        close(pipefd[0]);
        const char message[] = "Hello from child process through an IPC pipe!";
        write(pipefd[1], message, sizeof(message));
        close(pipefd[1]);
        _exit(0);
    }

    close(pipefd[1]);
    char buffer[256]{};
    ssize_t n = read(pipefd[0], buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        std::cout << "\n=== IPC Pipe Example ===\n";
        std::cout << "Parent received: " << buffer << '\n';
    } else {
        std::cerr << "read() failed or returned no data.\n";
    }
    close(pipefd[0]);
    waitpid(pid, nullptr, 0);
}
