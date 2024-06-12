# aetherOS

Welcome to the aether project! This project is an operating system, designed by @rebbelliondev and @Toni-Graphics. Right now, we are just starting, and you can expect changes to this code. 

At this moment, we are working on Memory. For specifically what we are working on in memory, see this link: (https://osdev.miraheze.org/wiki/Paging)

To run this kernel, you can use:

```
make run
```
OR:
```
make run-log
```
for running qemu with logs.

## Debugging
To debug aetherOS you need to run:
```
make debug
```
Then you can connect via gdb:
```
make gdb
```

> Type c to in the gdb console to execute the os
> ! it is slower than usual

This should make the .iso file and run it.

