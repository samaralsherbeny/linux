# Persistent Environment Variable Setup in Bash

This document provides a line-by-line breakdown and explanation of the terminal commands shown across the two terminal tabs/screenshots. The demonstration illustrates how to export an environment variable using `~/.bashrc` so that it persists across subshells and new terminal sessions.

---

## Command Breakdown & Explanations

### First Terminal Tab

#### 1. Open Configuration File in Text Editor
```bash
samar@samar-VMware-Virtual-Platform:~$ nano ~/.bashrc
```
* **Command:** `nano ~/.bashrc`
* **Explanation:** Opens the `~/.bashrc` configuration file in the `nano` text editor. Here, an environment variable declaration line (e.g., `export COMPANY="ITI"`) was added to make the variable persistent across shell instances.

---

#### 2. Reload Bash Configuration File
```bash
samar@samar-VMware-Virtual-Platform:~$ source ~/.bashrc
```
* **Command:** `source ~/.bashrc`
* **Explanation:** Reads and executes the commands from `~/.bashrc` in the current shell environment, instantly applying any added or updated environment variables without needing to restart the terminal session.

---
#### 3. Verify Environment Variable Value
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $COMPANY
ITI
```
* **Command:** `echo $COMPANY`
* **Explanation:** Displays the value stored in the `$COMPANY` variable. The output `ITI` confirms that the variable was successfully set and loaded into the current shell session.

---

#### 4. Test Persistence in a Subshell
```bash
samar@samar-VMware-Virtual-Platform:~$ bash -c 'echo $COMPANY'
ITI
```
* **Command:** `bash -c 'echo $COMPANY'`
* **Explanation:** Launches a new non-interactive child Bash subshell and executes the command `echo $COMPANY` inside it. The output `ITI` demonstrates that because the variable was exported in `~/.bashrc`, child processes inherit the environment variable.

---

### Second Terminal Tab

#### 5. Verify Variable Availability in a New Terminal Tab
```bash
samar@samar-VMware-Virtual-Platform:~$ echo $COMPANY
ITI
```
* **Command:** `echo $COMPANY`
* **Explanation:** Tested in a separate terminal tab. Because `~/.bashrc` automatically executes whenever a new interactive subshell/tab is opened, `$COMPANY` is automatically set to `ITI` without requiring manual intervention.

* #📸 output

* <img width="1325" height="511" alt="task2 1" src="https://github.com/user-attachments/assets/0911446d-2dbe-464b-8eb9-d58181510b5e" />

<img width="1324" height="473" alt="task2 2" src="https://github.com/user-attachments/assets/7627b02f-2a10-4f76-8a21-0176f72af2b9" />

