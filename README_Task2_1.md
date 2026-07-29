# Linux Environment & Shell Information Commands

This document provides a line-by-line breakdown and explanation of the Linux terminal session shown in the screenshot. These commands demonstrate how to inspect environment variables, current process details, user information, and system paths.

---

## Command Breakdown & Explanations

### 1. Identify Default Shell
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $SHELL
/bin/bash
```
* **Command:** `echo $SHELL`
* **Explanation:** Displays the absolute path of the default shell configured for the current user environment (`/bin/bash`).

---

### 2. Get Current Shell Process ID (PID)
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $$
4269
```
* **Command:** `echo $$`
* **Explanation:** `$$` is a special parameter in Bash that returns the Process ID (PID) of the currently executing shell process (in this case, `4269`).

---

### 3. Get Parent Process ID (PPID)
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $PPID
4242
```
* **Command:** `echo $PPID`
* **Explanation:** `$PPID` stores the Process ID of the process that spawned the current shell (e.g., the terminal emulator application or SSH daemon, here PID `4242`).

---

### 4. Identify Logged-in Username
```bash
samar@samar-VMware-Virtual-Platform:~$ whoami
samar
```
* **Command:** `whoami`
* **Explanation:** Prints the effective username of the currently logged-in user (`samar`).

---

### 5. Print Working Directory
```bash
samar@samar-VMware-Virtual-Platform:~$ pwd
/home/samar
```
* **Command:** `pwd`
* **Explanation:** Stands for "Print Working Directory". It outputs the full path of the directory you are currently located in (`/home/samar`).

---

### 6. Display Home Directory Path
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $HOME
/home/samar
```
* **Command:** `echo $HOME`
* **Explanation:** Prints the value stored in the `$HOME` environment variable, which defines the path to the current user's home directory.

---

### 7. Display System Hostname
```bash
samar@samar-VMware-Virtual-Platform:~$ hostname
samar-VMware-Virtual-Platform
```
* **Command:** `hostname`
* **Explanation:** Displays the network name assigned to the system host machine (`samar-VMware-Virtual-Platform`).

---

### 8. Fetch Default Shell via User Account Database
```bash
samar@samar-VMware-Virtual-Platform:~$ getent passwd $USER | cut -d: -f7
/bin/bash
```
* **Command:** `getent passwd $USER | cut -d: -f7`
* **Explanation:** 
  * `getent passwd $USER`: Queries the system's passwd database for the entry corresponding to the current user (`samar`).
  * `|`: Pipes the output of the first command as input into the second command.
  * `cut -d: -f7`: Uses `:` as a field delimiter (`-d:`) and extracts the 7th field (`-f7`), which stores the user's default login shell (`/bin/bash`).

---


### 9. View Executable Search Path
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin
```
* **Command:** `echo $PATH`
* **Explanation:** Prints the `$PATH` environment variable, which contains a colon-separated list of directory paths where the system looks for executable binary programs when commands are typed.

---


### 10. Count Total Environment Variables
```bash
samar@samar-VMware-Virtual-Platform:~$ env | wc -l
55
```
* **Command:** `env | wc -l`
* **Explanation:** 
  * `env`: Lists all exported environment variables in the current session.
  * `wc -l`: Counts the number of lines output by `env`. The result (`55`) indicates that there are currently 55 environment variables set in this session.
 
# 📸 output 

<img width="994" height="643" alt="task1" src="https://github.com/user-attachments/assets/f3785c05-8512-4d4c-96e3-5de082aca139" />

* **Explanation:** Prints the effective username of the currently logged-in user (`samar`).

---
