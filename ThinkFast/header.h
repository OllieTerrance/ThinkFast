#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// general helper methods
namespace Utils {
    // screen class provides abstraction over "sections" of the game
    class Screen {
    public:
        Screen();
        virtual ~Screen();
        virtual void init();
        virtual void draw(sf::RenderWindow& window);
        virtual void keypress(sf::Event::KeyEvent& key);
    };
    // game class abstracts individual mini-games
    class Game {
        enum State {InProgress, Win, Lose};
        State current;
    public:
        Game();
        virtual ~Game();
        virtual void draw(sf::RenderWindow& window);
        virtual void keypress(sf::Event::KeyEvent& key);
        virtual char* getPrompt();
    };
    // text-related
    void makeText(sf::Text& base, sf::Font& font, const char* str, int size, sf::Color colour, int style);
    void makeText(sf::Text& base, sf::Text* outlines, sf::Font& font, const char* str, int size,
                  sf::Color colour, sf::Color outlineColour, int style);
    void centreText(sf::Text& base, bool horiz, bool vert);
    void moveOutlineText(sf::Text& base, sf::Text* outlines, int shift);
    // mathematical
    int mod(int a, int b);
}

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
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& key);
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
    enum State {InProgress, Win, Lose};
    void init();
    void draw(sf::RenderWindow& window);
    void keypress(sf::Event::KeyEvent& key);
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
        const char* images[3] = {"space", "enter", "up"};
        void draw(sf::RenderWindow& window);
        void keypress(sf::Event::KeyEvent& key);
        char* getPrompt();
    };
}
