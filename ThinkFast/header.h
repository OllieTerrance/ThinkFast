#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// general helper methods
class Utils {
public:
    static sf::Font font;
    // screen class provides abstraction over "sections" of the game
    class Screen {
    public:
        Screen();
        virtual ~Screen();
        virtual void init();
        virtual void draw();
        virtual void keypress(sf::Event::KeyEvent& key);
    };
    // text-related
    static void makeText(sf::Text& base, sf::Font& font, const char* str, int size, sf::Color colour, int style);
    static void centreText(sf::Text& base, bool horiz, bool vert);
    // mathematical
    static int mod(int a, int b);
};

// manager allows switching between screens
class Manager {
    sf::RenderWindow& window;
    int current;
    Utils::Screen* screens[2];
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
    void draw();
    void keypress(sf::Event::KeyEvent& key);
};

// actual gameplay screen
class Game : public Utils::Screen {
    Manager& manager;
    int lives;
    int score;
    int countdown;
    sf::Clock clock;
    int state;
public:
    Game(Manager& newManager);
    ~Game();
    void init();
    void draw();
    void keypress(sf::Event::KeyEvent& key);
};
