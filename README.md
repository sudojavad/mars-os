# MarsOS
MarsOS is a simple 64-bit operating system developed for learning    
Feel free to contribute to MarsOS

# Build & Run   
Make sure you have installed [qemu-system-x86_64](https://archlinux.org/packages/extra/x86_64/qemu)
```console
make && make run && make clean
```

# TODO
1. Move kernel to 0x100000 ✓
2. Save registers in interrupt handlers. the pusha, popa instructions not supported in 64-bit mode
3. Update Makefile   
4. Write Documents
5. Memory management ✓
6. Process management
     - scheduling
     - wait/exit
     - sleep
     - fork/exec
     - system calls
7. Filesystem
     - ATA
     - FAT16
     - FD
8. Network    
9. Refactoring kernel/proc
10. Write a loader to loading larger kernels and using the ATA
11. Append the ps1 to end of mars.img and load it at 0x20000
