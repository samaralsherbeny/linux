# Custom Shell Welcome Banner Configuration

This document provides a line-by-line explanation of the terminal session shown in the screenshot. It demonstrates how editing `~/.bashrc` can be used to display a customized system welcome message and environmental summary every time a new Bash shell session is loaded.

---

## Command Breakdown & Output Explanation

### 1. Edit Bash Configuration File
```bash
samar@samar-VMware-Virtual-Platform:~$ nano ~/.bashrc
```
* **Command:** `nano ~/.bashrc`
* **Explanation:** Opens the user's `~/.bashrc` configuration file in the `nano` text editor to add custom script logic (such as `echo` statements or system dynamic variables) that builds a custom startup banner.

---

### 2. Apply and Execute Changes
```bash
samar@samar-VMware-Virtual-Platform:~$ source ~/.bashrc
```
* **Command:** `source ~/.bashrc`
* **Explanation:** Re-executes the updated `~/.bashrc` script directly in the active shell environment, triggering the newly configured custom banner output.

---
## Output Banner Breakdown

```text
========================================
       Welcome to ITI Linux Environment
========================================
User        : samar
Hostname    : samar-VMware-Virtual-Platform
Date        : Wed Jul 29 05:55:33 PM EEST 2026
Shell       : /bin/bash
Current Dir : /home/samar

Have a productive day!
----------------------------------------
```

### Banner Elements Explanation:

* **Header Banner:** Printed using decorative equal signs (`=`) and header text (`Welcome to ITI Linux Environment`).
* **User (`samar`):** Fetched dynamically using `$USER` or `whoami`.
* **Hostname (`samar-VMware-Virtual-Platform`):** Fetched dynamically using `$HOSTNAME` or `hostname`.
* **Date (`Wed Jul 29 05:55:33 PM EEST 2026`):** Generated using the `date` command output.
* **Shell (`/bin/bash`):** Retrieved from the `$SHELL` environment variable.
* **Current Dir (`/home/samar`):** Fetched dynamically using `$PWD` or `pwd`.
* **Footer Message:** A custom sign-off message (`Have a productive day!`) printed before returning control to the standard command prompt.

#📸 output 

<img width="1314" height="593" alt="task3" src="https://github.com/user-attachments/assets/3abbe0e1-fa81-419d-b16c-85e50f403208" />
