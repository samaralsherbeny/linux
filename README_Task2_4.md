# Custom Bash Command: print_content
Documentation for defining, reloading, and executing the custom print_content Bash command in a Linux/Ubuntu environment.

Overview
This setup adds a custom command (print_content) to the user's ~/.bashrc configuration file. Executing print_content displays the detailed contents of the current directory, including hidden dotfiles (equivalent to running ls -la).

Setup Instructions
1. Edit the .bashrc File
Open the Bash configuration file in the nano text editor:

nano ~/.bashrc

Add the following alias definition to the end of the file:

alias print_content="ls -la"

Save and exit (Ctrl + O, Enter, then Ctrl + X).

2. Apply Changes
Reload your .bashrc file so the changes take effect in the current terminal session:

source ~/.bashrc

3. Run the Command
Execute your new custom command:

print_content

Sample Output
total 88
drwxr-x--- 16 samar samar 4096 Jul 30 17:14 .
drwxr-xr-x  3 root  root  4096 Jul 12 16:49 ..
-rw-------  1 samar samar 1534 Jul 29 17:59 .bash_history
-rw-r--r--  1 samar samar  220 Feb 13 14:16 .bash_logout
-rw-r--r--  1 samar samar 4058 Jul 30 17:14 .bashrc
-rw-r--r--  1 samar samar 5010 Jul 29 17:59 .bashrc.save
drwx------ 13 samar samar 4096 Jul 29 17:18 .cache
drwx------ 15 samar samar 4096 Jul 30 14:17 .config
drwx------  4 samar samar 4096 Jul 12 16:57 .local
-rw-r--r--  1 samar samar  807 Feb 13 14:16 .profile
drwx------  2 samar samar 4096 Jul 28 17:15 .ssh
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Desktop
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Documents
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Downloads
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Music
drwxr-xr-x  3 samar samar 4096 Jul 28 16:46 Pictures
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Public
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Templates
drwxr-xr-x  2 samar samar 4096 Jul 12 16:57 Videos
drwxrwxr-x  2 samar samar 4096 Jul 27 14:58 my_folder
drwx------  7 samar samar 4096 Jul 23 21:00 snap
