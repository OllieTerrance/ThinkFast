#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// general helper methods
class Utils {
public:
	// screen class provides abstraction over "sections" of the game
	class Screen {
	protected:
		sf::RenderWindow& window;
	public:
		Screen(sf::RenderWindow& newWindow);
		virtual void draw() = 0;
		virtual void keypress(sf::Event::KeyEvent& key) = 0;
	};
    static void setFont(sf::Font& newFont);
    static void makeText(sf::Text& base, const char* str, int size, sf::Color colour, int style);
    static void centreText(sf::Text& base, bool horiz, bool vert);
};

// main menu screen
class Menu : public Utils::Screen {
    int selIndex = 0;
    int players = 1;
public:
	Menu(sf::RenderWindow& newWindow);
    void draw();
    void keypress(sf::Event::KeyEvent& key);
};
