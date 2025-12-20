[README.md](https://github.com/user-attachments/files/24271166/README.md)
<h1 align="center">Welcome to EnseaSH 👋</h1>
<p>
  <img alt="Version" src="https://img.shields.io/badge/version-1.0-blue.svg?cacheSeconds=2592000" />
  <a href="http://manpagesfr.free.fr/man/man2/open.2.html" target="_blank">
    <img alt="Documentation" src="https://img.shields.io/badge/documentation-yes-brightgreen.svg" />
  </a>
</p>

> Create a micro shell that displays the exit codes and execution times

### 🏠 [Homepage](https://github.com/EtudiantEnsea)


# enseash

A simple micro shell developed in C as part of the ENSEA Systems Programming course.

---

## Description

`enseash` is a minimal Unix shell that allows the execution of external commands.
It displays the exit status (or signal) and execution time of the previously
executed command.

The shell supports:
- Execution of simple commands and commands with arguments starting from question 6
- Input and output redirections (`<` and `>`)
- Exit using `exit` or `Ctrl+D`

---


## Compilation

To compile the question x:

```sh
gcc questionx.c -o enseash
./enseah
```
## Documentation

write() :
https://pubs.opengroup.org/onlinepubs/009695099/functions/write.html

read() :
https://pubs.opengroup.org/onlinepubs/009604599/functions/read.html

strlen() :
https://pubs.opengroup.org/onlinepubs/9699919799/

strcmp() :
https://pubs.opengroup.org/onlinepubs/9699919799/

fork() :
https://pubs.opengroup.org/onlinepubs/9699919799/

clock_gettime() :
https://pubs.opengroup.org/onlinepubs/9699919799/

open() :
https://pubs.opengroup.org/onlinepubs/007904875/functions/open.html

dup2() :
https://pubs.opengroup.org/onlinepubs/9699919799/








## Author

👤 **Loick GOMES GRANCHO & Houssam BEKRI**
