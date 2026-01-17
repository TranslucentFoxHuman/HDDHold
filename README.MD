# HDDHold
## What is this?
This program writes a random byte sequence to a file at specified intervals. By doing so, it prevents the hard disk from sleeping or the head from retracting when it has gone unused for a while. Frequent head retractions and disk stop/start cycles shorten the lifespan of a hard disk.

On Unix, it was sufficient to run the shell script in the **Running on Unix** section below. However, Windows does not have a special file like `/dev/urandom` that produces random numbers, so I developed a C program that performs the same task. For this reason, the project is cross‑platform but primarily developed for Windows.

## Build instructions
This code can be compiled with gcc or clang. The Microsoft Visual C++ compiler is not supported.  
There are no dependencies or Makefiles, so just pass the source files to the compiler.  
On Windows we recommend using `gcc` from [MinGW‑w64](https://github.com/niXman/mingw-builds-binaries/releases).

With `gcc`, you can compile on either Windows or Unix with a command like:
```sh
gcc hddhold.c -o hddhold.exe
```

## Usage
```
-b <bytes>    : Set the size of the random data in bytes (default: 4)
-i <interval> : Set the interval (in seconds) at which to perform the write (default: 4)
-o <filename> : Set the file to which random data will be written (default: C:\hddhold)
-h --help     : Print this help message
-v --version  : Print program version
```

Example:
```
hddhold.exe -b 4 -i 4 -o C:\hddhold.bin
```

When the program starts, it will continue writing a random byte sequence of the specified size (default 4 bytes) to the specified file (default `C:\hddhold`) every specified number of seconds (default 4 seconds). To stop it, press **Ctrl + C** in the terminal or send a termination signal from Task Manager or a similar tool.

## Running on Unix
Although this program is cross‑platform, on Unix you no longer need to run a program like this; a simple shell script is sufficient:

```bash
#!/bin/sh
while true; do
    dd bs=1 count=4 if=/dev/urandom of=/hddhold 2> /dev/null
    sleep 4
done
```

# License
This program is provided under the GNU General Public License Version 3 or later. See `gpl-3.0.txt` for details.