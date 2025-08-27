# Turtle Graphics in C

A linked-list based **Turtle Graphics interpreter**, written in C.  
This project was originally part of **CSCA48 (Intro to Computer Science II, University of Toronto Scarborough)**, and extended with additional features such as **nested loops** for more complex drawings.

**Note**: This repository is published for **educational and portfolio purposes only**.  
It is **not intended for reuse in coursework**.

---

## Features

### Base Version (`turtle.c`)
- Stores drawing commands in a **linked list**.
- Supports basic operations:
  - `penup`, `pendown`
  - `forward`, `backward`
  - `right`, `left`
  - `colour`
- Insert, update, and delete commands dynamically.
- Render line drawings using a simple raster image utility.

### Extended Version (`turtle-pro.c`)
- Adds a **`loop` construct** to repeat a sequence of commands.
- Supports **nested loops** for advanced shapes and patterns.
- Demonstrates handling of recursive data structures and control flow.

---

## File Structure
├── turtle.c # Base interpreter
├── turtle-pro.c # Extended version with loops
├── imgUtils.c/h # Simple image utility functions (not included here)
├── Makefile # Build script (optional)
└── README.md # Project documentation

> Note: `imgUtils.c/h` were part of the original starter code.  
If you want to run this project, you need to provide equivalent image-drawing utilities or stub functions.

---

## Compilation & Usage

Using `gcc` directly:

```bash
# Compile base version
gcc turtle.c -o turtle

# Compile extended version
gcc turtle-pro.c -o turtle-pro

Then run:
./turtle
./turtle-pro

Expected workflow:
Input a sequence of turtle commands (or load from a file).
The program stores commands in a linked list.
Execute to produce a raster image output (e.g., .ppm format).

Example Commands
pendown
forward 100
right 90
forward 50
penup
loop 4 [
  forward 30
  right 90
]

Disclaimer
This project is based on coursework from CSCA48 (University of Toronto Scarborough).
All modifications and extensions are my own work.
It is shared here as part of my personal learning portfolio and should not be reused for academic submissions.
