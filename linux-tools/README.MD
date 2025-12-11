# 🛠️ Linux Tools — Recreated from Scratch

Part of the jeydevlearnslinux project: rebuilding Unix userland tools using pure C and Linux syscalls.

This folder contains the source code for each tool, compiled binaries, and tests.

# 📁 Folder Structure

```bash
linuxtools/
│
├── src/
│   ├── cat/
│   │   └── cat.c
│   │
│   └── echo/
│       └── echo.c
│
├── bin/
│   ├── cat
│   └── echo
│
├── tests/
    ├── test_cat.sh
    └── test_echo.sh


```

## ✅ Implemented Tools

1. `cat`
   Reimplementation of the Unix `cat` utility using:
   > - open()
   > - read()
   > - write()
   > - error handling & buffers
2. `echo`
   Simple printing tool to output arguments to stdout.
3. `pwd`
   Simple printing tool to output current working directory.
