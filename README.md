# brsh

brsh is a small, bash-like, shell built from scratch in c++. The shell has the ability to execute all of the normal external programs that a shell should be able to execute, support for pipes, IO redirection, and a short list of builtin commands. 

The builtin commands are as follows:

  - cd: change directories
  - exit: exit the shell
  - brsh: print the shells ascii art, authors, and version info
  - history: view your command history for the current shell session
  - r <#>: re-run a previously run command from the history log
