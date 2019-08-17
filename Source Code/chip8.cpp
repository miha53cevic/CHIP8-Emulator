#include "chip8.h"
#include <ctime>

chip8::chip8()
{
    srand(time(0));
}

chip8::~chip8()
{
}

void chip8::CPUReset()
{
    m_AdressI = 0;
    m_ProgramCounter = 0x200; // Game is loaded into 0x200 so the first instruction is there
    memset(m_Registers, 0, sizeof(m_Registers)); // Set registers to 0
    memset(m_GameMemory, 0, sizeof(m_GameMemory)); // Set Memory to 0

    loadRom();
}

void chip8::loadRom()
{
    FILE *in;
    if (in = fopen("roms/Space Invaders.ch8", "rb"))
    {
        fread(&m_GameMemory[0x200], 0xfff, 1, in);
        fclose(in);

        printf("Loaded rom successfuly\n");
    }
    else printf("Could not load rom!\n");
}

WORD chip8::getNextOpcode()
{
    // To create the result we have to combine 2 memory spots to get a 2 BYTE long opcode
    // so memory at 0x200 and 0x201 should be combined to create the opcode
    // since both are 1byte long we shift 0x200 8 spaces to the left and do a
    // logical OR operation to add the second memory slot thus resulting in a 2BYTE opcode

    WORD result = 0; // opcode
    result = m_GameMemory[m_ProgramCounter];
    result <<= 8; // Shift 8 times left
    result = result | m_GameMemory[m_ProgramCounter + 1]; // Combine with logical OR, with the next spot in memory
    m_ProgramCounter += 2; // Move the program counter to the next opcode

    return result;
}

void chip8::ExecuteOpcode()
{
    /*
        DECODING EXAMPLE for OPCODE 0x1234

        WORD firstNumber = opcode & 0xF000 ; // would give 0x1000
        WORD secondNumber = opcode & 0x0F00 ; // would give 0x0200
        WORD secondAndLast = opcode & 0x0F0F ; // would give 0x0204
        WORD lastTwoNumbers = opcode & 0x00FF ; // would give 0x0034
    */

    WORD opcode = getNextOpcode();

    // Decode Opcode
    switch (opcode & 0xF000)
    {
        case 0x0000: DecodeOpcode0(opcode); break;
        case 0x1000: Opcode1NNN(opcode); break;
        case 0x2000: Opcode2NNN(opcode); break;
        case 0x3000: Opcode3XNN(opcode); break;
        case 0x4000: Opcode4XNN(opcode); break;
        case 0x5000: Opcode5XY0(opcode); break;
        case 0x6000: Opcode6XNN(opcode); break;
        case 0x7000: Opcode7XNN(opcode); break;
        case 0x8000: DecodeOpcode8(opcode); break;
        case 0x9000: Opcode9XY0(opcode); break;
        case 0xA000: OpcodeANNN(opcode); break;
        case 0xB000: OpcodeBNNN(opcode); break;
        case 0xC000: OpcodeCXNN(opcode); break;
        case 0xD000: OpcodeDXYN(opcode); break;
        case 0xE000: DecodeOpcodeE(opcode); break;
        case 0xF000: DecodeOpCodeF(opcode); break;

        default: std::cout << "Opcode not found!\n"; break;
    }
}

void chip8::DecodeOpcode0(WORD opcode)
{
    switch (opcode & 0x000F)
    {
        case 0x0: Opcode00E0(opcode); break;
        case 0xE: Opcode00EE(opcode); break;

        default: std::cout << "Opcode0 not found!\n"; break;
    }
}

void chip8::DecodeOpcode8(WORD opcode)
{
    switch (opcode & 0x000F)
    {
        case 0x0: Opcode8XY0(opcode); break;
        case 0x1: Opcode8XY1(opcode); break;
        case 0x2: Opcode8XY2(opcode); break;
        case 0x3: Opcode8XY3(opcode); break;
        case 0x4: Opcode8XY4(opcode); break;
        case 0x5: Opcode8XY5(opcode); break;
        case 0x6: Opcode8XY6(opcode); break;
        case 0x7: Opcode8XY7(opcode); break;
        case 0xE: Opcode8XYE(opcode); break;

        default: std::cout << "Opcode8 not found!\n"; break;
    }
}

void chip8::DecodeOpcodeE(WORD opcode)
{
    switch (opcode & 0x000F)
    {
        case 0xE: OpcodeEX9E(opcode); break;
        case 0x1: OpcodeEXA1(opcode); break;

        default: std::cout << "OpcodeE not found!\n"; break;
    }
}

void chip8::DecodeOpCodeF(WORD opcode)
{
    switch (opcode & 0x00FF)
    {
    case 0x07: OpcodeFX07(opcode); break;
    case 0x0A: OpcodeFX0A(opcode); break;
    case 0x15: OpcodeFX15(opcode); break;
    case 0x18: OpcodeFX18(opcode); break;
    case 0x1E: OpcodeFX1E(opcode); break;
    case 0x29: OpcodeFX29(opcode); break;
    case 0x33: OpcodeFX33(opcode); break;
    case 0x55: OpcodeFX55(opcode); break;
    case 0x65: OpcodeFX65(opcode); break;

    default: std::cout << "OpcodeF not found!\n"; break;
    }
}
/*
    OPCODE Definitions
*/
void chip8::Opcode00E0(WORD opcode)
{
    // Clear display
}

void chip8::Opcode00EE(WORD opcode)
{
    m_ProgramCounter = m_stack.top();
    m_stack.pop();
}

void chip8::Opcode1NNN(WORD opcode)
{
    m_ProgramCounter = opcode & 0x0FFF;
}

void chip8::Opcode2NNN(WORD opcode)
{
    m_stack.push(m_ProgramCounter);
    m_ProgramCounter = opcode & 0x0FFF;
}

void chip8::Opcode3XNN(WORD opcode)
{
    int nn = opcode & 0x00FF;
    int regx = opcode & 0x0F00;
    regx >>= 8; // shift jer inace dobimo 0x200, a ako shiftamo dobijemo 0x2, hex znamenku mozemo prikazati pomocu 4 bita znaci da ako hocemo pomaknuti za jedno mjesto znamenku shiftamo 4, a s obzirom da hocemo 2 mjesta pomaknuti shifta se 8

    if (m_Registers[regx] == nn)
        m_ProgramCounter += 2;
}

void chip8::Opcode4XNN(WORD opcode)
{
    int nn = opcode & 0x00FF;
    int regx = opcode & 0x0F00;
    regx >>= 8;

    if (m_Registers[regx] != nn)
        m_ProgramCounter += 2;
}

void chip8::Opcode5XY0(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4; // shift 4 jer se dobije 0x20, a trazi se 0x2

    if (m_Registers[regx] == m_Registers[regy])
        m_ProgramCounter += 2; // skip next instruction
}

void chip8::Opcode6XNN(WORD opcode)
{
    int nn = opcode & 0x00FF;
    int regx = opcode & 0x0F00;
    regx >>= 8;

    m_Registers[regx] = nn;
}

void chip8::Opcode7XNN(WORD opcode)
{
    int nn = opcode & 0x00FF;
    int regx = opcode & 0x0F00;
    regx >>= 8;

    m_Registers[regx] += nn;
}

void chip8::Opcode8XY0(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;

    m_Registers[regx] = m_Registers[regy];
}

void chip8::Opcode8XY1(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;

    m_Registers[regx] = m_Registers[regx] | m_Registers[regy];
}

void chip8::Opcode8XY2(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;

    m_Registers[regx] = m_Registers[regx] & m_Registers[regy];
}

void chip8::Opcode8XY3(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;

    m_Registers[regx] = m_Registers[regx] ^ m_Registers[regy];
}

void chip8::Opcode8XY4(WORD opcode)
{
    m_Registers[0xF] = 0;
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;

    int value = m_Registers[regx] + m_Registers[regy];

    if (value > 255)
        m_Registers[0xF] = 1;

    m_Registers[regx] = m_Registers[regx] + m_Registers[regy];
}

void chip8::Opcode8XY5(WORD opcode)
{
    m_Registers[0xF] = 0;
    int regx = opcode & 0x0F00; // mask off reg x
    regx = regx >> 8; // shift x across 
    int regy = opcode & 0x00F0; // mask off reg y 
    regy = regy >> 4; // shift y across 

    int xval = m_Registers[regx];
    int yval = m_Registers[regy];

    if (xval > yval) 
        m_Registers[0xF] = 1;

    m_Registers[regx] = xval - yval;
}

void chip8::Opcode8XY6(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;

    m_Registers[0xF] = m_Registers[regx] & 0x1;
    m_Registers[regx] >>= 1;
}

void chip8::Opcode8XY7(WORD opcode)
{
    m_Registers[0xF] = 0;
    int regx = opcode & 0x0F00; // mask off reg x
    regx = regx >> 8; // shift x across 
    int regy = opcode & 0x00F0; // mask off reg y 
    regy = regy >> 4; // shift y across 

    int xval = m_Registers[regx];
    int yval = m_Registers[regy];

    if (xval < yval)
        m_Registers[0xF] = 1;

    m_Registers[regx] = yval - xval;
}

void chip8::Opcode8XYE(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;

    m_Registers[0xF] = m_Registers[regx] >> 7;
    m_Registers[regx] <<= 1;
}

void chip8::Opcode9XY0(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4; // shift 4 jer se dobije 0x20, a trazi se 0x2

    if (m_Registers[regx] != m_Registers[regy])
        m_ProgramCounter += 2; // skip next instruction
}

void chip8::OpcodeANNN(WORD opcode)
{
    m_AdressI = opcode & 0x0FFF;
}

void chip8::OpcodeBNNN(WORD opcode)
{
    int nnn = opcode & 0x0FFF;
    m_ProgramCounter = nnn + m_Registers[0];
}

void chip8::OpcodeCXNN(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int nn = opcode & 0x00FF;

    m_Registers[regx] = nn & (rand() % 256);
}

void chip8::OpcodeDXYN(WORD opcode)
{
    // Draws on the screen
    
    int regx = opcode & 0x0F00;
    regx = regx >> 8;
    int regy = opcode & 0x00F0;
    regy = regy >> 4;

    int height = opcode & 0x000F;
    int coordx = m_Registers[regx];
    int coordy = m_Registers[regy];

    m_Registers[0xf] = 0;

    // loop for the amount of vertical lines needed to draw
    for (int yline = 0; yline < height; yline++)
    {
        BYTE data = m_GameMemory[m_AdressI + yline];
        int xpixelinv = 7;
        int xpixel = 0;

        for (xpixel = 0; xpixel < 8; xpixel++, xpixelinv--)
        {
            int mask = 1 << xpixelinv;
            if (data & mask)
            {
                int x = coordx + xpixel;
                int y = coordy + yline;

                if (m_ScreenData[y][x] == 1)
                    m_Registers[0xF] = 1; //collision

                m_ScreenData[y][x] ^= 1;
            }
        }
    }
}

void chip8::OpcodeEX9E(WORD opcode)
{
    // Key pressed instruction
}

void chip8::OpcodeEXA1(WORD opcode)
{
    // Key pressed instruction
}

void chip8::OpcodeFX07(WORD opcode)
{
    // delay timer value
}

void chip8::OpcodeFX0A(WORD opcode)
{
    // Key press instruction
}

void chip8::OpcodeFX15(WORD opcode)
{
    // Delay timer
}

void chip8::OpcodeFX18(WORD opcode)
{
    // Sound timer
}

void chip8::OpcodeFX1E(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;

    m_AdressI = m_AdressI + m_Registers[regx];
}

void chip8::OpcodeFX29(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;
    m_AdressI = m_Registers[regx] * 5;
}

void chip8::OpcodeFX33(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;

    int value = m_Registers[regx];

    int hundreds = value / 100;
    int tens = (value / 10) % 10;
    int units = value % 10;

    m_GameMemory[m_AdressI] = hundreds;
    m_GameMemory[m_AdressI + 1] = tens;
    m_GameMemory[m_AdressI + 2] = units;
}

void chip8::OpcodeFX55(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;

    for (int i = 0; i <= regx; i++)
    {
        m_GameMemory[m_AdressI + i] = m_Registers[i];
    }

    m_AdressI = m_AdressI + regx + 1;
}

void chip8::OpcodeFX65(WORD opcode)
{
    int regx = opcode & 0x0F00;
    regx >>= 8;

    for (int i = 0; i <= regx; i++)
    {
        m_Registers[i] = m_GameMemory[m_AdressI + i];
    }

    m_AdressI = m_AdressI + regx + 1;
}
