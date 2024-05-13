# CPU_Emulator

A simple CPU emulator mostly based on my understanding of computers and CPUs, written in C++17.

## Requirements
- A C++17 compatible compiler.
- CMake >= 3.20

## Building
```bash
$ cmake -B build -S
$ cmake --build build
```

## Usage
First, you should provide a source code with the following instructions:
- ADD <LEFT> <RIGHT>
- DUMP
- EXIT

> NOTE: You should write one instruction per-line

For example:
```txt
ADD
20
30
DUMP
EXIT
```

Then:
```bash
$ ./build/cpu my_asm.cpu

--------------------------------

0 14 1e 1


Memory usage: 4B

Registers:

A: 20
B: 30
C: 50
I: 1

--------------------------------

```

