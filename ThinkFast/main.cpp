#include "header.h"

#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
    sf::Font font;
    if (!font.loadFromFile("fonts/Cantarell.ttf")) {
        return 1;
    }
    Utils::setFont(font);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Think Fast");
    Utils::Screen* screen;
    screen = new MainMenu(window);
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    screen->keypress(event.key);
                    break;
                default:
                    break;
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw stuff
        screen->draw();
        // end the current frame
        window.display();
    }
    return 0;
}
