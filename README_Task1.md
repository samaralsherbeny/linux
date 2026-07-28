# Task 1:

## 📌type command:   

the 'type' command tells how the shell interprets a command when you run it

### 🔷 Example 1: Basic Usage 

```bash
type ls
```
the 'type ls ' it shows that ls is actually an alias (a shortcut).

### 📸 command output

<img width="1650" height="300" alt="type ls" src="https://github.com/user-attachments/assets/eac52686-fcbe-43e1-916f-8daf663af96b" />

### 🔷Example 2: Using -a Flag

```bash
type -a ls
```

The '-a' flag tells type to show all matching locations and definitions for ls, not just the first one it finds.

### 📸 command output 

 <img width="1655" height="263" alt="type -a ls" src="https://github.com/user-attachments/assets/ba99501f-e5eb-4d9d-80d7-dc8e48a028d0" />

## 📌which command:

The 'which' command searches your system's PATH to find the absolute path of the executable file.

### 🔷Example:

```bash
which ls
```
it ignores the shell alias and points directly to where the binary file lives on your system

### 📸 command output 

<img width="1665" height="217" alt="which ls" src="https://github.com/user-attachments/assets/ee34375d-95f2-4726-9a3f-5dd1e54bae2e" />

## 📌file utility:

The 'file' utility inspects a file's contents to determine its exact file type.

### 🔷Example:

```bash
file /usr/bin/ls
```
### 📸 utility output 

<img width="1655" height="185" alt="file utility" src="https://github.com/user-attachments/assets/1bc01e90-5e86-4071-8bd2-21289651153d" />

### 📌 cd usage:

```bash
which cd
```

```bash
type cd
```

### 📸 output 

<img width="1643" height="148" alt="cd" src="https://github.com/user-attachments/assets/496369e9-5806-4b43-9086-12dc9d1b0b8b" />

## 📌 system calls (strace):

### 🔷 Example 1:

```bash
sudo apt install strace -y
```

Installs strace, a diagnostic tool that intercepts and logs all system calls made by a process.

### 📸 output 

<img width="1645" height="182" alt="install strace" src="https://github.com/user-attachments/assets/a58a61b4-f669-4ba4-9faa-fb2baf792963" />

### 🔷 Example 2:

```bash
strace -c ls /etc
```

Runs ls /etc and prints a summarized statistical table (-c) showing which system calls were used and how many times.

### 📸 output 

<img width="1638" height="149" alt="strace" src="https://github.com/user-attachments/assets/001497d3-f860-4a5f-93b1-7507e10fe20c" />

### 🔷 Example 3:

```bash
strace ls /tmp 2>&1 | head -30
```

Intercepts the first 30 system calls executed when running ls /tmp.

### 📸 output

<img width="1645" height="455" alt="tmp" src="https://github.com/user-attachments/assets/ba0b70f8-daa5-418f-aeb2-c6cd95cca3ac" />

## 📌 Everything is a file:

### 🔷 Example 1:

```bash
ls -l /dev/sda
```

Interacts with a physical hard drive/SSD (/dev/sda) as if it were a simple device file.

### 📸 output

<img width="1503" height="129" alt="sda" src="https://github.com/user-attachments/assets/11d93306-a359-4816-b948-1b8f9323727a" />

### 🔷 Example 2:

``bash
cat /proc/cpuinfo
```

Reads live processor information generated on the fly by the kernel inside the virtual /proc file system

### 📸 output

<img width="1659" height="679" alt="cpu" src="https://github.com/user-attachments/assets/8d88a018-78e4-45c0-9a2e-aa9ca4c9fee0" />

### 🔷 Example 3:

``bash
cat /proc/meminfo
```

Reads real-time RAM usage statistics.

### 📸 output

<img width="837" height="811" alt="meminfo" src="https://github.com/user-attachments/assets/cd7fe8fb-3692-47b3-ad1b-d8ea9285c4ab" />

### 🔷 Example 4:

``bash
ls /proc/$$/
```

Views all running details (memory maps, file descriptors, status) of your current shell process

### 📸 output

<img width="1639" height="194" alt="proc" src="https://github.com/user-attachments/assets/952dd440-da93-45f1-ba02-99f798db9588" />

### 🔷 Example 5:

``bash
cat /sys/class/net/*/address
```

Reads network interface MAC addresses directly from system files.

### 📸 output

<img width="1355" height="116" alt="net" src="https://github.com/user-attachments/assets/c81084d4-c6c3-4004-9f19-bb4ad97c4250" />

### 🔷 Example 6:

```bash
echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward
```

Enables IP packet forwarding by simply writing the character '1' into a kernel parameter file

### 📸 output

<img width="1653" height="142" alt="ip" src="https://github.com/user-attachments/assets/0be98fe7-8368-4062-a641-5f84cb8df195" />

## 📌 Exit status:

0 = success, anything else = failure.

### 🔷 Example 1:

```bash
ls /etc
echo $?
```
### 📸 output

<img width="1656" height="425" alt="Ubuntu 64-bit-2026-07-28-17-57-27" src="https://github.com/user-attachments/assets/4aa35c61-af82-4bf4-b6c6-3dff04652fd4" />

### 🔷 Example 2:

```bash
ls /nonexistent
echo $? 
```

### 📸 output

<img width="1639" height="141" alt="fault" src="https://github.com/user-attachments/assets/37f5b141-99de-42ee-b2a0-b4dfa37fced0" />

## 📌 man:

