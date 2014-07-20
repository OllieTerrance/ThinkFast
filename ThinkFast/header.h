#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// general helper methods
class Utils {
public:
    // screen class provides abstraction over "sections" of the game
    class Screen {
    public:
        Screen();
        virtual ~Screen();
        virtual void draw() = 0;
        virtual void keypress(sf::Event::KeyEvent& key) = 0;
    };
    // text-related helpers
    static void setFont(sf::Font& newFont);
    static void makeText(sf::Text& base, const char* str, int size, sf::Color colour, int style);
    static void centreText(sf::Text& base, bool horiz, bool vert);
};

// manager allows switching between screens
class Manager {
    sf::RenderWindow& window;
    int current = 0;
    Utils::Screen* screens[2];

public:
    Manager(sf::RenderWindow& window);
    ~Manager();
    sf::RenderWindow& getWindow();
    void setCurrent(int pos);
    Utils::Screen& getScreen();
    Utils::Screen& getScreen(int pos);
};

// main menu screen
class Menu : public Utils::Screen {
    Manager& manager;
    int selIndex = 0;
    int players = 1;
public:
    Menu(Manager& newManager);
    ~Menu();
    void draw();
    void keypress(sf::Event::KeyEvent& key);
};

// actual gameplay screen
class Game : public Utils::Screen {
    Manager& manager;
public:
    Game(Manager& newManager);
    ~Game();
    void draw();
    void keypress(sf::Event::KeyEvent& key);
};
