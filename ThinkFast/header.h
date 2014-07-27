#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// constants and macros
#define ERR_ASSET 2
#define MAX_PLAYERS 8
#define MOD(a, b) (((a) % (b)) + (b)) % (b)

// general helper methods
namespace Utils {
    // screen class provides abstraction over "sections" of the game
    class Screen {
    public:
        Screen();
        virtual ~Screen();
        virtual void init();
        virtual void draw(sf::RenderWindow& window);
        virtual void keypress(sf::Event::KeyEvent& key, bool on);
        virtual void joybutton(sf::Event::JoystickButtonEvent& button, bool on);
    };
    // game class abstracts individual mini-games
    class Game {
        enum State {InProgress, Win, Lose};
        State current;
    public:
        Game();
        virtual ~Game();
        virtual void draw(sf::RenderWindow& window);
        virtual void keypress(sf::Event::KeyEvent& key, bool on);
        virtual void joybutton(sf::Event::JoystickButtonEvent& button, bool on);
        virtual std::string getPrompt();
    };
    // text-related
    void makeText(sf::Text& base, sf::Font& font, std::string str, int size, sf::Color colour, int style);
    void makeText(sf::Text& base, sf::Text* outlines, sf::Font& font, std::string str, int size,
                  sf::Color colour, sf::Color outlineColour, int style);
    void centreText(sf::Text& base, bool horiz, bool vert);
    void moveOutlineText(sf::Text& base, sf::Text* outlines, int shift);
    // sound-related
    void playSound(sf::SoundBuffer& buffer, sf::Sound& sound, std::string path);
}

// manager allows switching between screens
class Manager {
    sf::RenderWindow& window;
    int current;
    Utils::Screen* screens[3];
    sf::Font font;
public:
    Manager(sf::RenderWindow& window);
    ~Manager();
    sf::RenderWindow& getWindow();
    void setCurrent(int pos);
    Utils::Screen& getScreen();
    Utils::Screen& getScreen(int pos);
    sf::Font& getFont();
};

// main menu screen
class Menu : public Utils::Screen {
    Manager& manager;
    int selIndex;
    int players;
public:
    Menu(Manager& newManager);
    ~Menu();
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& key, bool on);
    void joybutton(sf::Event::JoystickButtonEvent& button, bool on);
};

// control test screen
class Controls : public Utils::Screen {
    Manager& manager;
    bool pressed[MAX_PLAYERS];
public:
    Controls(Manager& newManager);
    ~Controls();
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& key, bool on);
    void joybutton(sf::Event::JoystickButtonEvent& button, bool on);
};

// actual gameplay screen
class Play : public Utils::Screen {
    Manager& manager;
    int lives;
    sf::Texture heart;
    int score;
    int countdown;
    sf::Clock clock;
    Utils::Game* game;
public:
    Play(Manager& newManager);
    ~Play();
    enum State {Countdown, InProgress, Win, Lose};
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& key, bool on);
    void joybutton(sf::Event::JoystickButtonEvent& button, bool on);
    sf::Time getTime();
    void win();
    void lose();
private:
    State current;
};

namespace Games {
    class PressButton : public Utils::Game {
        Play& parent;
        sf::Texture bg;
        int index;
        int widths[3] = {110, 89, 56};
        int heights[3] = {55, 43, 36};
    public:
        PressButton(Play& newParent);
        ~PressButton();
        enum Button {Space, Enter, Up};
        const std::string images[3] = {"space", "enter", "up"};
        void draw(sf::RenderWindow& window);
        void keypress(sf::Event::KeyEvent& key, bool on);
        void joybutton(sf::Event::JoystickButtonEvent& button, bool on);
        std::string getPrompt();
    };
}
