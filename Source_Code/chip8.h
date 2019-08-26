#pragma once
#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <stack>
#include <fstream>
#include <iostream>
#include <cstdint> // Allows uint8_t

/*
// WORD 16-bit
// BYTE  8-bit
*/

class chip8
{
public:
    chip8();
    ~chip8();

    void KeyPressed(int key);
    void KeyReleased(int key);

    void Run();
    void loadRom(std::string fileName);

    void DecreaseTimers();

    uint8_t getScreenData(int x, int y);

    uint8_t getRegister(int index);
    uint8_t getKeyState(int index);

private:
    uint8_t m_GameMemory[0xFFF];
    uint8_t m_Registers[16];
    uint16_t m_AdressI;
    uint16_t m_ProgramCounter;
    std::stack<uint16_t> m_stack;

    uint8_t m_ScreenData[32][64];
    uint8_t m_KeyState[16];

    uint8_t m_DelayTimer;
    uint8_t m_Soundtimer;

private:
    void CPUReset();

    uint16_t getNextOpcode();
    void ExecuteOpcode();

    void DecodeOpcode0(uint16_t opcode);
    void DecodeOpcode8(uint16_t opcode);
    void DecodeOpcodeE(uint16_t opcode);
    void DecodeOpCodeF(uint16_t opcode);

private:
    // OPCODES
    //void Opcode0NNN(uint16_t opcode); Most roms don't use it
    void Opcode00E0(uint16_t opcode);
    void Opcode00EE(uint16_t opcode);
    void Opcode1NNN(uint16_t opcode);
    void Opcode2NNN(uint16_t opcode);
    void Opcode3XNN(uint16_t opcode);
    void Opcode4XNN(uint16_t opcode);
    void Opcode5XY0(uint16_t opcode);
    void Opcode6XNN(uint16_t opcode);
    void Opcode7XNN(uint16_t opcode);
    void Opcode8XY0(uint16_t opcode);
    void Opcode8XY1(uint16_t opcode);
    void Opcode8XY2(uint16_t opcode);
    void Opcode8XY3(uint16_t opcode);
    void Opcode8XY4(uint16_t opcode);
    void Opcode8XY5(uint16_t opcode);
    void Opcode8XY6(uint16_t opcode);
    void Opcode8XY7(uint16_t opcode);
    void Opcode8XYE(uint16_t opcode);
    void Opcode9XY0(uint16_t opcode);
    void OpcodeANNN(uint16_t opcode);
    void OpcodeBNNN(uint16_t opcode);
    void OpcodeCXNN(uint16_t opcode);
    void OpcodeDXYN(uint16_t opcode);
    void OpcodeEX9E(uint16_t opcode);
    void OpcodeEXA1(uint16_t opcode);
    void OpcodeFX07(uint16_t opcode);
    void OpcodeFX0A(uint16_t opcode);
    void OpcodeFX15(uint16_t opcode);
    void OpcodeFX18(uint16_t opcode);
    void OpcodeFX1E(uint16_t opcode);
    void OpcodeFX29(uint16_t opcode);
    void OpcodeFX33(uint16_t opcode);
    void OpcodeFX55(uint16_t opcode);
    void OpcodeFX65(uint16_t opcode);
};

