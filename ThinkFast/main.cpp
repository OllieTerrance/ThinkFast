#include "header.h"

#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
    // load font
    sf::Font font;
    if (!font.loadFromFile("fonts/Cantarell.ttf")) return 1;
    Utils::setFont(font);
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Think Fast", sf::Style::Titlebar | sf::Style::Close);
    Utils::Screen* screen = new Menu(window);
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all events since last iteration
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    // quit on close
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    // pass keypress to current screen
                    screen->keypress(event.key);
                    break;
                default:
                    break;
            }
        }
        // start all black
        window.clear(sf::Color::Black);
        // draw from screen
        screen->draw();
        // end the current frame
        window.display();
    }
    return 0;
}
