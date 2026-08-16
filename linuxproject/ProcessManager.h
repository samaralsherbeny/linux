#pragma once

class ProcessManager {
public:
    void listProcesses() const;
    void showProcessInfo(int pid) const;
    int createChildProcess() const;
    void sendSignal(int pid, int signalNumber) const;
};
