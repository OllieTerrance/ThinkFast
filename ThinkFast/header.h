#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// general helper methods
class Utils {
public:
	class Screen {
	protected:
		sf::RenderWindow& window;
	public:
		Screen(sf::RenderWindow& newWindow) : window(newWindow) {}
		virtual void draw() = 0;
		virtual void keypress(sf::Event::KeyEvent& key) = 0;
	};
    static void setFont(sf::Font& newFont);
    static void makeText(sf::Text& base, const char* str, int size, sf::Color colour, int style);
    static void horizCentreText(sf::Text& base);
};

// main menu screen
class MainMenu : public Utils::Screen {
    int selIndex = 0;
    int players = 1;
public:
	MainMenu(sf::RenderWindow& newWindow) : Utils::Screen(newWindow) {}
    void draw();
    void keypress(sf::Event::KeyEvent& key);
};
