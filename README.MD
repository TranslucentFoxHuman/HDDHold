# HDDHold
## What is this?
This program writes a random byte sequence to a file at specified intervals. By doing so, it prevents the hard disk from sleeping or the head from retracting when it has gone unused for a while. Frequent head retractions and disk stop/start cycles shorten the lifespan of a hard disk.

On Unix, it was sufficient to run the shell script in the **Running on Unix** section below. However, Windows does not have a special file like `/dev/urandom` that produces random numbers, so I developed a C program that performs the same task. For this reason, the project is cross‑platform but primarily developed for Windows.

## Build instructions
This code can be compiled with any compilers. With improvements to the code, it can also be compiled with the Visual C++ compiler. It can even be compiled with very old compilers that only support C89.

There are no dependencies or Makefiles, so you can build it by simply passing the source file to the compiler.

If you use gcc, you can compile it on both Windows and Unix with a command like the following.  
For Windows, you can use [MinGW‑w64](https://github.com/niXman/mingw-builds-binaries/releases).

```bash
gcc hddhold.c -O2 -o hddhold.exe
```

If you use Visual C++, compile it with a command such as:

```cmd
cl hddhold.c /Fehddhold.exe /MD /O2
```

The `/MD` and `/O2` options are not mandatory, but specifying `/MD` makes the file size very small, and specifying `/O2` speeds up execution. Because this program runs as a background service, these options are recommended.

If you use OpenWatcom, you can do it like this. It is usually not recommended, but it can be used in very old environments where MinGW or Visual C++ are not available, such as Windows 9x‑style systems.

```bash
wcl386 -bcl=win95 -fe=hddhold.exe hddhold.c
```

Although it is completely useless, using OpenWatcom also allows you to compile for MS‑DOS.  
Since it does not run as a resident program in MS‑DOS, it is really just a toy there :)

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