#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stack>
#include <fstream>
#include <iostream>

typedef unsigned char BYTE;      //  8-bits
typedef unsigned short int WORD; // 16-bits

class chip8
{
public:
    chip8();
    ~chip8();

    void Run();
    void KeyPressed(int key);
    void KeyReleased(int key);

    BYTE* getScreenData();

private:
    BYTE m_GameMemory[0xFFF];
    BYTE m_Registers[16];
    WORD m_AdressI;
    WORD m_ProgramCounter;
    std::stack<WORD> m_stack;

    BYTE m_ScreenData[32][64];
    BYTE m_KeyState[16];

    BYTE m_DelayTimer;
    BYTE m_Soundtimer;

private:
    void CPUReset();
    void loadRom();

    WORD getNextOpcode();
    void ExecuteOpcode();

    void DecodeOpcode0(WORD opcode);
    void DecodeOpcode8(WORD opcode);
    void DecodeOpcodeE(WORD opcode);
    void DecodeOpCodeF(WORD opcode);

private:
    // OPCODES
    //void Opcode0NNN(WORD opcode); Most roms don't use it
    void Opcode00E0(WORD opcode);
    void Opcode00EE(WORD opcode);
    void Opcode1NNN(WORD opcode);
    void Opcode2NNN(WORD opcode);
    void Opcode3XNN(WORD opcode);
    void Opcode4XNN(WORD opcode);
    void Opcode5XY0(WORD opcode);
    void Opcode6XNN(WORD opcode);
    void Opcode7XNN(WORD opcode);
    void Opcode8XY0(WORD opcode);
    void Opcode8XY1(WORD opcode);
    void Opcode8XY2(WORD opcode);
    void Opcode8XY3(WORD opcode);
    void Opcode8XY4(WORD opcode);
    void Opcode8XY5(WORD opcode);
    void Opcode8XY6(WORD opcode);
    void Opcode8XY7(WORD opcode);
    void Opcode8XYE(WORD opcode);
    void Opcode9XY0(WORD opcode);
    void OpcodeANNN(WORD opcode);
    void OpcodeBNNN(WORD opcode);
    void OpcodeCXNN(WORD opcode);
    void OpcodeDXYN(WORD opcode);
    void OpcodeEX9E(WORD opcode);
    void OpcodeEXA1(WORD opcode);
    void OpcodeFX07(WORD opcode);
    void OpcodeFX0A(WORD opcode);
    void OpcodeFX15(WORD opcode);
    void OpcodeFX18(WORD opcode);
    void OpcodeFX1E(WORD opcode);
    void OpcodeFX29(WORD opcode);
    void OpcodeFX33(WORD opcode);
    void OpcodeFX55(WORD opcode);
    void OpcodeFX65(WORD opcode);
};

