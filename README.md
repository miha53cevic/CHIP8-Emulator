# CHIP8-Emulator
CHIP8 emulator written in C++ / SFML

![](https://media.giphy.com/media/KAdjN9gcGXQcrJy4E6/giphy.gif)

## CHIP8 Programs & Games
https://github.com/dmatlack/chip8/tree/master/roms

## Literature used
- https://www.miniwebtool.com/bitwise-calculator/ 
  - used for figuring out hex operations
- https://en.wikipedia.org/wiki/CHIP-8
  - has all the opcodes and a good overview of the system
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#00EE
  - has extra information and more detailed opcodes, some are different than the wiki but the wiki ones were used in these situations

## How to build
  ```bash
  git clone https://github.com/miha53cevic/CHIP8-Emulator.git
  cd CHIP8-Emulator
  cmake .
  make
  ```
You should now have a bin folder with an executable
