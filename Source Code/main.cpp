#include "mihaSimpleSFML.h"
#include "chip8.h"

#include <fstream>

class App : public mihaSimpleSFML
{
public:
    App()
    {
        // Try and load settings.ini if it exists
        std::ifstream in("settings.ini");
        if (!in.fail())
        {
            std::string line;

            while (!in.eof())
            {
                in >> line;

                if (line == "OpcodesPerFrame")
                {
                    in >> m_OpcodesPerFrame;
                    m_OpcodesPerFrame /= 60;

                    std::cout << "Loaded custom OpcodesPerFrame\n";
                }
                else std::cout << "Could not find line OpcodesPerFrame!";
            }
        }
        else
        {
            std::cout << "Could not open settings.ini\n";

            // Default speed --> opcodes / FPS = opcodes per frame
            m_OpcodesPerFrame = 400 / 60;
        }
    }

private:
    chip8 m_emulator;

    unsigned int m_OpcodesPerFrame;

private:
    void DrawPixel(int x, int y, int width)
    {
        sf::RectangleShape pixel;
        pixel.setSize(sf::Vector2f(width, width));
        pixel.setPosition(x, y);
        pixel.setFillColor(sf::Color::Black);

        Draw(pixel);
    }

private:
    void Event(sf::Event e) override
    {
        if (e.type == sf::Event::KeyPressed)
        {
            int key = -1;

            switch (e.key.code)
            {
                case sf::Keyboard::Numpad0: key = 0; break;
                case sf::Keyboard::Numpad1: key = 1; break;
                case sf::Keyboard::Numpad2: key = 2; break;
                case sf::Keyboard::Numpad3: key = 3; break;
                case sf::Keyboard::Numpad4: key = 4; break;
                case sf::Keyboard::Numpad5: key = 5; break;
                case sf::Keyboard::Numpad6: key = 6; break;
                case sf::Keyboard::Numpad7: key = 7; break;
                case sf::Keyboard::Numpad8: key = 8; break;
                case sf::Keyboard::Numpad9: key = 9; break;
                case sf::Keyboard::Q: key = 10; break;
                case sf::Keyboard::W: key = 11; break;
                case sf::Keyboard::E: key = 12; break;
                case sf::Keyboard::A: key = 13; break;
                case sf::Keyboard::S: key = 14; break;
                case sf::Keyboard::D: key = 15; break;
            }

            #ifdef DEBUG
                        std::cout << "Key pressed: " << key << std::endl;
            #endif // DEBUG


            if (key != -1)
                m_emulator.KeyPressed(key);
        }
        else if (e.type == sf::Event::KeyReleased)
        {
            int key = -1;

            switch (e.key.code)
            {
                case sf::Keyboard::Numpad0: key = 0; break;
                case sf::Keyboard::Numpad1: key = 1; break;
                case sf::Keyboard::Numpad2: key = 2; break;
                case sf::Keyboard::Numpad3: key = 3; break;
                case sf::Keyboard::Numpad4: key = 4; break;
                case sf::Keyboard::Numpad5: key = 5; break;
                case sf::Keyboard::Numpad6: key = 6; break;
                case sf::Keyboard::Numpad7: key = 7; break;
                case sf::Keyboard::Numpad8: key = 8; break;
                case sf::Keyboard::Numpad9: key = 9; break;
                case sf::Keyboard::Q: key = 10; break;
                case sf::Keyboard::W: key = 11; break;
                case sf::Keyboard::E: key = 12; break;
                case sf::Keyboard::A: key = 13; break;
                case sf::Keyboard::S: key = 14; break;
                case sf::Keyboard::D: key = 15; break;
            }

            #ifdef DEBUG
                        std::cout << "Key released: " << key << std::endl;
            #endif // DEBUG

            if (key != -1)
                m_emulator.KeyReleased(key);
        }
    }

private:
    bool OnUserCreate() override
    {
        // Set background fill colour
        setBackgroundColor(sf::Color::White);

        // Set V-SYNC
        EnableVSync(true);

        // Load rom
        m_emulator.loadRom("Space Invaders");

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        // Run emulator / opcodes
        for (int i = 0; i < m_OpcodesPerFrame; i++)
            m_emulator.Run();

        m_emulator.DecreaseTimers();

        // Display Pixels
        for (int y = 0; y < 32; y++)
        {
            for (int x = 0; x < 64; x++)
            {
                if (m_emulator.getScreenData(x, y) == 1)
                {
                    DrawPixel(x * 10, y * 10, 10);
                }
            }
        }

        return true;
    }
};

int main()
{
    App app;
    app.Construct(640, 320, L"CHIP8 Emulator");
    app.Start();
    
    return 0;
}