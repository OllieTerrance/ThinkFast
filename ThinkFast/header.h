#include <iostream>
#include <map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// constants and macros
#define ERR_ASSET 1
#define ERR_JOY 2
#define SCR_MENU 0
#define SCR_CONTROLS 1
#define SCR_PLAY 2
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
        virtual void keypress(sf::Event::KeyEvent& event, bool on);
        virtual void joybutton(sf::Event::JoystickButtonEvent& event, bool on);
        virtual void joyaxis(sf::Event::JoystickMoveEvent& event);
    };
    // game class abstracts individual mini-games
    class Game {
        int players;
    public:
        Game();
        virtual ~Game();
        virtual void draw(sf::RenderWindow& window);
        virtual void keypress(sf::Event::KeyEvent& event, bool on);
        virtual void joybutton(sf::Event::JoystickButtonEvent& event, bool on);
        virtual void joyaxis(sf::Event::JoystickMoveEvent& event);
        virtual std::string getPrompt();
    };
    // text-related
    void makeText(sf::Text& base, sf::Font& font, std::string str, int size, sf::Color colour, int style);
    void makeText(sf::Text& base, sf::Text* outlines, sf::Font& font, std::string str, int size,
                  sf::Color colour, sf::Color outlineColour, int style);
    void centreText(sf::Text& base, bool horiz, bool vert);
    void moveOutlineText(sf::Text& base, sf::Text* outlines, int shift);
}

// manager allows switching between screens
class Manager {
    sf::RenderWindow& window;
    bool joysticks[sf::Joystick::Count];
    int players[sf::Joystick::Count];
    int playerCount;
    int current;
    Utils::Screen* screens[3];
    sf::Font font;
    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> sounds;
public:
    Manager(sf::RenderWindow& window);
    ~Manager();
    sf::RenderWindow& getWindow();
    bool* getJoysticks();
    Manager& setPlayerJoysticks(bool* joysticks);
    int* getPlayers();
    int getPlayerCount();
    int joyToPlayer(int joy);
    Manager& setCurrent(int pos);
    Utils::Screen& getScreen();
    Utils::Screen& getScreen(int pos);
    sf::Font& getFont();
    Manager& playSound(std::string name);
};

// main menu screen
class Menu : public Utils::Screen {
    Manager& manager;
    int selIndex;
    sf::Texture bg;
    sf::Clock clock;
public:
    Menu(Manager& newManager);
    ~Menu();
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& event, bool on);
    void joybutton(sf::Event::JoystickButtonEvent& event, bool on);
    void joyaxis(sf::Event::JoystickMoveEvent& event);
};

// control test screen
class Controls : public Utils::Screen {
    Manager& manager;
    bool pressed[sf::Joystick::Count];
    sf::Texture bg;
public:
    Controls(Manager& newManager);
    ~Controls();
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& event, bool on);
    void joybutton(sf::Event::JoystickButtonEvent& event, bool on);
};

// actual gameplay screen
class Play : public Utils::Screen {
    Manager& manager;
    int lives[sf::Joystick::Count];
    int score[sf::Joystick::Count];
    bool counting;
    int countdown;
    sf::Clock clock;
    Utils::Game* game;
    sf::Texture heart;
public:
    Play(Manager& newManager);
    ~Play();
    enum State {Progress, Win, Lose};
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& event, bool on);
    void joybutton(sf::Event::JoystickButtonEvent& event, bool on);
    void joyaxis(sf::Event::JoystickMoveEvent& event);
    int getActiveCount();
    int playerActive(int player);
    sf::Time getTime();
    State getState(int player);
    void win(int player);
    void lose(int player);
private:
    State state[sf::Joystick::Count];
};

namespace Games {
    class ButtonStack : public Utils::Game {
        Play& play;
        Manager& manager;
        int pos[sf::Joystick::Count];
        unsigned int stack[5];
    public:
        ButtonStack(Play& newPlay, Manager& newManager);
        ~ButtonStack();
        static const std::string buttons[4];
        static const sf::Color pendingColours[5];
        static const sf::Color doneColours[5];
        void draw(sf::RenderWindow& window);
        void joybutton(sf::Event::JoystickButtonEvent& event, bool on);
        std::string getPrompt();
    };
}
